# COS214PRAC5-CampusGuard

# CampusGuard Emergency Response System

CampusGuard is a C++ simulation of a university emergency management system. It heavily leverages Gang of Four (GoF) design patterns to coordinate complex responses, including **Command, Mediator, Facade, Adapter, State, and Memento**.

## Prerequisites

To run this project in an isolated environment, ensure you have the following installed:

* [Docker](https://docs.docker.com/get-docker/)

* [Docker Compose](https://docs.docker.com/compose/install/)

## Running with Docker (Recommended)

The project includes a `Dockerfile` and `docker-compose.yml` configured to automatically compile and run the application.

To build the image and run the simulation, execute the following command in the root directory:

```
docker compose up --build

```

**What this does:**

1. Pulls the base Ubuntu image and installs the necessary C++ build tools (`g++`, `make`, `valgrind`).

2. Copies the project source files into the container.

3. Runs `make clean && make` to compile the `campusguard` executable.

4. Executes `./campusguard` to output the runtime demonstration to your terminal.

## Running Locally (Without Docker)

If you prefer to compile the project locally on a Linux/Unix system with `g++` and `make` installed:

1. Compile the project:

   ```
   make
   
   ```

2. Run the executable:

   ```
   ./campusguard
   
   ```

3. Clean up compiled object files:

   ```
   make clean
   
   ```