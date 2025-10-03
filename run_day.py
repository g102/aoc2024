#! /usr/bin/env python
import pathlib
import subprocess
import sys

day = f"{int(sys.argv[1]):02d}"

parent = pathlib.Path(".").absolute()

script_dir = [_ for _ in parent.iterdir() if day in _.name]
if len(script_dir) == 0:
	raise UserWarning("Day not attempted yet!")
else:
	script_dir = script_dir[0]

script = script_dir / f"day{day}"
if not script.exists():
	raise UserWarning("Day not attempted yet!")

subprocess.call(f'{script}', shell=True, cwd=script_dir)
