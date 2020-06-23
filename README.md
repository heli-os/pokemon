[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/960813/pokemon">
    <img src="https://github.com/960813/pokemon/blob/master/_data/README.png?raw=true" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">Pokemon</h3>

  <p align="center">
    This repository is a very important project that I developed for the final exams in college.    
    <br />
    <a href="https://github.com/960813/pokemon"><strong>Explore the Github »</strong></a>
    <br />
    <br />
    <a href="https://www.youtube.com/playlist?list=PLhIMdWOb1dj-Us_Kz0CIfKQJmhKbF5OLj">View Demo</a>
    ·
    <a href="https://github.com/960813/pokemon/issues">Report Bug</a>
    ·
    <a href="https://github.com/960813/pokemon/issues">Request Feature</a>
  </p>
</p>


<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
  * [Main Features](#main-features)
  * [Built With](#built-with)
* [Usage](#usage)
* [Contributing](#contributing)
* [License](#license)
* [Contact](#contact)
* [Acknowledgements](#acknowledgements)



<!-- ABOUT THE PROJECT -->
## About The Project
[![Pokemon Screen Shot][product-screenshot]](https://www.youtube.com/playlist?list=PLhIMdWOb1dj-Us_Kz0CIfKQJmhKbF5OLj)

[![Pokemon Youtube](https://github.com/960813/pokemon/blob/master/_data/001.jpg?raw=true)](https://youtu.be/kbe0sB0oKbA)
[![Pokemon Youtube](https://github.com/960813/pokemon/blob/master/_data/002.jpg?raw=true)](https://youtu.be/JWqQ4Y0F4u0)
[![Pokemon Youtube](https://github.com/960813/pokemon/blob/master/_data/003.jpg?raw=true)](https://youtu.be/JWqQ4Y0F4u0)
[![Pokemon Youtube](https://github.com/960813/pokemon/blob/master/_data/004.jpg?raw=true)](https://youtu.be/Jw6UiKjsano)

This is an online Pokemon game where data is synchronized to the central server.
### Main Features
* Custom Allegro5 framework for graphic rendering
* Game state change function (update) and rendering function (render) based on function pointer
* GameLauncher for game access
* Player rendering, movement, action
* Item used, acquired (with gold system)
* Battle with Gym Leader and Wild Pokemon
* Synchronize data with UNIX Socket On AWS

### Built With
* Client: MSVC
* Server: GCC
* Game Launcher: C#(CSharp)

<!-- USAGE EXAMPLES -->
## Usage
1. Set up dependency
    - Client: Allegro5 in NuGet, jansson
    - Server: jansson, MySQL-lib
2. Configure Server Property
3. Run Server
4. Run GameLauncher
5. Register Account and Login
6. Play

<!-- CONTRIBUTING -->
## Contributing
This repository is not managed.

<!-- LICENSE -->
## License
Distributed under the MIT License. See `LICENSE` for more information.

<!-- CONTACT -->
## Contact
JIN TAEYANG - sun@jupiterflow.com

Project Link: [https://github.com/960813/pokemon](https://github.com/960813/pokemon)


<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements
* [Allegro5](https://liballeg.org/)
* [MariaDB](https://mariadb.org)
* [Jansson](https://digip.org/jansson/)



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/960813/pokemon?style=flat-square
[contributors-url]: https://github.com/960813/pokemon/graphs/contributors

[forks-shield]: https://img.shields.io/github/forks/960813/pokemon?style=flat-square
[forks-url]: https://github.com/960813/pokemon/network/members

[stars-shield]: https://img.shields.io/github/stars/960813/pokemon?style=flat-square
[stars-url]: https://github.com/960813/pokemon/stargazers

[issues-shield]: https://img.shields.io/github/issues/960813/pokemon?style=flat-square
[issues-url]: https://github.com/960813/pokemon/issues

[license-shield]: https://img.shields.io/github/license/960813/pokemon?style=flat-square
[license-url]: https://github.com/960813/pokemon/blob/master/LICENSE

[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=flat-square&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/jupiterflow

[product-screenshot]: https://github.com/960813/pokemon/blob/master/_data/000.png?raw=true