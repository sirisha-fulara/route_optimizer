# Base image with Ubuntu 22.04 for stability on Render
FROM ubuntu:22.04

# Install Python, pip, and build tools
RUN apt-get update && apt-get install -y \
    python3 python3-pip python3-dev build-essential g++ \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy requirements and install Python dependencies
COPY requirements.txt .
RUN pip3 install -r requirements.txt

# Copy your entire project files
COPY . .

# Compile your C++ code into shared object (.so)
RUN g++ -O3 -Wall -shared -std=c++17 -fPIC \
    -I$(python3 -m pybind11 --includes | sed -e 's/-I//g') \
    cpp_backend/route_optimizer.cpp -o cpp_backend/route_optimizer.cpython-312-x86_64-linux-gnu.so


# Expose the port your app will run on
EXPOSE 10000

# Start your Flask app with gunicorn on port 10000
CMD ["gunicorn", "--bind", "0.0.0.0:10000", "test:app"]
