CREATE TABLE users (
    id SERIAL PRIMARY KEY,
    username VARCHAR(255) NOT NULL,
    password VARCHAR(255) NOT NULL,
    email VARCHAR(255) NOT NULL
);

INSERT INTO users (username, password, email) VALUES
('admin', 'adminpassword', 'admin@admin.com'),
('user', 'userpassword', 'user@user.com');

CREATE TABLE products (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    description TEXT,
    price DECIMAL(10, 2) NOT NULL
);

INSERT INTO products (name, description, price) VALUES
('Product 1', 'Description of Product 1', 9.99),
('Product 2', 'Description of Product 2', 19.99);

