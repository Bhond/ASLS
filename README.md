# Introduction

This little project is just a way to get some fun coding algorithms 
and get used to frameworks. Nothing fancy and still pretty raw, not really properly refactored.

The current aim is to play with A Simple Life Simulation (ASLS) using the NEAT algorithm.

# State of the art

A video is on its way to just present more easily what it does without having to download the project
and setting it up.

# Contribution

For those who want to play with it and/or develop on top of it, here are my recommended steps and the minimal configuration:

I only compiled it on windows x64. (Linux on its way, maybe...). I am using Visual Studio 2022.

Make sure cmake is installed and that you can compile c++.

- Install **VCPKG**:
	Follow these steps: https://vcpkg.io/en/getting-started.html
	
- Using **VCPKG**, you'll need:
	1. Qt5:x64-windows (very long...)
	2. SFML:x64-windows

Launch the project, compile it all and you should be good to go.