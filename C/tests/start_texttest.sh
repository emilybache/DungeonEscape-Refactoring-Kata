#!/bin/sh

python -m venv venv
source venv/bin/activate
python -m pip install -r requirements.txt

texttest -d . "$@"
