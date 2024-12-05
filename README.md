[![Progress][progress-shield]][progress-url]
[![Issues][issues-shield]][issues-url]
<a name="readme-top"></a>

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/CodecoolGlobal/cpp-satelite-sniffer-cpp-davidszoki">
    <img src="resources/Images/ISS (ZARYA).png" alt="Logo" width="200" height="200">
  </a>

<h3 align="center">Satellite Sniffer</h3>

  <p align="center">
    Satellite Sniffer Readme documentiation
    <br />
    <a href="https://github.com/CodecoolGlobal/cpp-satelite-sniffer-cpp-davidszoki"><strong>Explore the docs »</strong></a>
    <br />
    <br />
  </p>
</div>


<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#about-the-project">About The Project</a></li>
    <li><a href="#features">Features</a></li>
    <li><a href="#setup">Setup</a></li>
    <li><a href="#optional-setup">Optional setup</a></li>
    <li><a href="#built-with">Built With</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->

## About The Project
<a name="about-the-project"></a>

The application displays the desired satellite orbits on a 2D representation of Earth.
When the application starts, it initially shows the paths of two satellites (ISS (ZARYA) and HST) relative to Earth.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


## Features
<a name="features"></a>

### Display the satellites listed in `Satellites.txt`
### Show the GMT time corresponding to the satellite's current position.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


## Setup
<a name="setup"></a>

### Clone the repository

### Install `vcpkg` packages

#### SDL2
#### SDL2-Images
#### SDL2-TTF

### Install Python Interpreter and packages

#### `pip`
#### `ephem`

### Build the application by the `CMakeLists.txt`


## Optional Setup: Add more satellites to display in addition to the above
<a name="optional-setup"></a>

### Register at https://www.space-track.org to fetch TLE data for the desired satellites

### Set environment variables for the build and fetch process

#### `USERNAME`
#### `PASSWORD`

### Provide image for the satellite in `png` format

### Add exact name of satellite (NORAD name) and NORAD ID separated by `;` to `Satellites.txt`

### Example: `ISS (ZARYA);25544` 

<p align="right">(<a href="#readme-top">back to top</a>)</p>


## Built With
<a name="built-with"></a>

[![C++][C++]][C++-url]<br>
[![Python][Python]][Python-url]<br>


<p align="right">(<a href="#readme-top">back to top</a>)</p>


[progress-shield]: https://img.shields.io/badge/In-Progress-8B0000.svg?style=for-the-badge

[progress-url]: https://github.com/CodecoolGlobal/cpp-satelite-sniffer-cpp-davidszoki/blob/main/README.md#progress

[issues-shield]: https://img.shields.io/github/issues/CodecoolGlobal/cpp-satelite-sniffer-cpp-davidszoki.svg?style=for-the-badge

[issues-url]: https://github.com/CodecoolGlobal/cpp-satelite-sniffer-cpp-davidszoki/issues

[Python]: https://img.shields.io/badge/Python-3776AB?logo=python&logoColor=fff

[Python-url]: https://www.python.org/

[C++]: https://img.shields.io/badge/C++-%2300599C.svg?logo=c%2B%2B&logoColor=white

[C++-url]: https://cplusplus.com/

