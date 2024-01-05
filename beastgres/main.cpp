#include "json.hpp"
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <cstdlib>
#include <iostream>
#include <libpq-fe.h>
#include <memory>
#include <string>
#include <thread>
namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;
using json = nlohmann::json;
// Function to handle the database connection and queries
std::string handle_database(const std::string &requestData) {
  using json = nlohmann::json;

  PGconn *conn = PQconnectdb(
      "user=user password=password dbname=mydb hostaddr=172.19.0.1 port=5432");
  if (PQstatus(conn) != CONNECTION_OK) {
    std::cerr << "Connection to database failed: " << PQerrorMessage(conn)
              << std::endl;
    PQfinish(conn);
    return "Database connection failed";
  }

  json requestJson = json::parse(requestData);
  std::string method = requestJson.value("method", "");
  if (method == "login") {
    std::string username = requestJson.value("username", "");
    std::string password = requestJson.value("password", "");

    // Use prepared statements to avoid SQL injection
    const char *paramValues[2];
    paramValues[0] = username.c_str();
    paramValues[1] = password.c_str();

    PGresult *res = PQexecParams(
        conn, "SELECT * FROM users WHERE username = $1 AND password = $2",
        2,    // number of params
        NULL, // let the library deduce param type
        paramValues,
        NULL, // don't need param lengths since text
        NULL, // default to all text params
        0);   // ask for text results
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
      std::cerr << "SELECT failed: " << PQerrorMessage(conn) << std::endl;
      PQclear(res);
      PQfinish(conn);
      return "Query execution failed";
    }
    // Check if any row is returned
    if (PQntuples(res) > 0) {
      PQclear(res);
      PQfinish(conn);
      return "Login successful";
    } else {
      PQclear(res);
      PQfinish(conn);
      return "Login failed";
    }
  } else if (method == "register") {
    // Parse the received data
    json data = json::parse(requestData); // Assuming req_body is a JSON string
    std::string email = data["email"];
    std::string username = data["username"];
    std::string password = data["password"];

    // Sanitize inputs (using parameterized queries)

    // Prepare statement
    PGresult *res = PQprepare(
        conn, "insert_user",
        "INSERT INTO users(email, username, password) VALUES ($1, $2, $3)", 0,
        NULL);

    // Execute with sanitized inputs
    const char *paramValues[3] = {email.c_str(), username.c_str(),
                                  password.c_str()};
    res = PQexecPrepared(conn, "insert_user", 3, paramValues, NULL, NULL, 0);

    // Check execution status
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
      std::cerr << "Insert failed: " << PQerrorMessage(conn) << std::endl;
      PQclear(res);
      PQfinish(conn);
      return "Registration error";
    }

    PQclear(res);
    PQfinish(conn);
    return "Registration successful";
  } else if (method == "products") {
    PGresult *res = PQexec(conn, "SELECT * FROM products");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
      std::cerr << "SELECT failed: " << PQerrorMessage(conn) << std::endl;
      PQclear(res);
      PQfinish(conn);
      return "Failed to retrieve products";
    }

    int nrows = PQntuples(res);
    int nfields = PQnfields(res);
    json products = json::array();

    for (int i = 0; i < nrows; i++) {
      json product;
      for (int j = 0; j < nfields; j++) {
        product[PQfname(res, j)] = PQgetvalue(res, i, j);
      }
      products.push_back(product);
    }

    PQclear(res);
    PQfinish(conn);
    return products.dump();
  } else {
    PQfinish(conn);
    return "Unknown method";
  }
}
// Function to handle HTTP requests and respond
void handle_request(http::request<http::string_body> &req,
                    http::response<http::string_body> &res) {
  if (req.method() != http::verb::post || req.target() != "/api/db") {
    res = http::response<http::string_body>(http::status::bad_request,
                                            req.version());
    res.body() = "Invalid request";
    res.prepare_payload();
    return;
  }

  std::string response = handle_database(req.body());
  res = http::response<http::string_body>(http::status::ok, req.version());
  res.body() = response;
  res.prepare_payload();
}

// Main server loop
void do_listen(net::io_context &ioc, tcp::endpoint endpoint) {
  beast::error_code ec;
  tcp::acceptor acceptor(ioc, endpoint, false);
  acceptor.listen(net::socket_base::max_listen_connections, ec);

  while (true) {
    tcp::socket socket(ioc);
    acceptor.accept(socket, ec);
    if (!ec) {
      beast::tcp_stream stream(std::move(socket));
      beast::flat_buffer buffer;

      http::request<http::string_body> req;
      http::read(stream, buffer, req, ec);
      if (!ec) {
        http::response<http::string_body> res;
        handle_request(req, res);
        http::write(stream, res, ec);
      }
    }
  }
}

int main() {
  net::io_context ioc{1};
  auto const address = net::ip::make_address("0.0.0.0");
  unsigned short port = static_cast<unsigned short>(std::atoi("8000"));
  do_listen(ioc, tcp::endpoint{address, port});
  return 0;
}
