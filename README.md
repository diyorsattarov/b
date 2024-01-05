# beastgres-app

## Introduction
`beastgres-app` is a comprehensive demonstration of a full-stack application integrating a REST API with PostgreSQL database interaction and an Express.js backend. This project showcases efficient database management using the libpq library, robust SQL utilization, and containerization with Docker for both backend services and the frontend server.

## Directory Structure
```
~/ (beastgres-app)
|-- boostbase/
|-- Dockerfile 
|-- beastgres/ 
| |-- Dockerfile 
| |-- CMakeLists.txt
| |-- *.cpp (C++ files) 
| |-- *.sql (SQL scripts) 
|-- express/
| |-- Dockerfile
| |-- package.json
| |-- *.js (JavaScript files)
| |-- public/
| |-- views/
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
- **User Registration:** Successfully registers new users through the Express.js server, communicating with the PostgreSQL database.
- **Dockerization:** Each component (REST API and PostgreSQL database) is containerized for easy deployment and scalability.

