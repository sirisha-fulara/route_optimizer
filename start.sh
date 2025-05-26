#!/bin/bash

export LD_LIBRARY_PATH=/opt/render/project/src/cpp_backend/libs:$LD_LIBRARY_PATH

gunicorn test:app