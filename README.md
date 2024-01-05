# postgres-rest-service

## Introduction
`postgres-rest-service` is a minimal yet robust demonstration of a REST API utilizing the libpq library for PostgreSQL database interaction. This project highlights efficient database management, SQL utilization, and containerization with Docker.

## Directory Structure
```
~/ (postgres-rest-service)
|-- boostbase/
|-- Dockerfile 
|-- beastgres/ 
| |-- Dockerfile 
| |-- CMakeLists.txt
| |-- *.cpp (C++ files) 
| |-- *.sql (SQL scripts) 
`-- Docker-compose.yaml
```

## Building and Running
1. **Prerequisites:** Ensure Docker and Docker Compose are installed on your system.
2. **Build the Containers:**
   - Navigate to the project root.
   - Run `docker-compose build` to build the images specified in `Docker-compose.yaml`.
3. **Run the Services:**
   - Execute `docker-compose up` to start the services.
   - The REST API will be accessible at the specified port.

## Key Features
- **REST API:** Efficient handling of HTTP requests with a focus on CRUD operations.
- **Database Interaction:** Usage of the libpq library for PostgreSQL, demonstrating database connection, querying, and transaction management.
- **SQL and PostgreSQL:** Application of SQL scripts for database schema creation and management.
- **Dockerization:** Each component (REST API and PostgreSQL database) is containerized for easy deployment and scalability.

