import re
import os

def to_screaming_snake(name):
    name = re.sub(r'(Component|Tag)$', '', name)
    s1 = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1_\2', s1).upper()

def to_snake_case(name):
    s1 = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1_\2', s1).lower()

def to_screaming_space(name):
    s1 = re.sub('(.)([A-Z][a-z]+)', r'\1 \2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1 \2', s1).upper()

def save_if_changed(filename, content):
    should_write = True

    if os.path.exists(filename):
        with open(filename, "r", encoding="utf-8") as existing_file:
            if existing_file.read() == content:
                should_write = False

    if should_write:
        with open(filename, "w", encoding="utf-8") as f:
            f.write(content)