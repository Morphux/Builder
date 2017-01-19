BUILDER
=======

# What for ?
- Building packages automatically for all architectures supported by Morphux
- Extracting binaries
- Extracting installed files (Configuration)
- Extracting meta information on the package: Build time, size, ...
- Update the Morphux Package Database

# Solution
- A deamon server listening on local
- This daemon must execute requests asked by a crawler / manually
- This daemon must build the package
- This daemon must extract information about the said package
- This daemon must be able to execute concurrent builds

# Infrastructure

## Git server
The git server is used for package development and configuration.
When a maintainer want to release a package, he push the code into a branch
named: 
```
package_name-version
```

When this happen, the crawler is trigerred to launch a build.

## Crawler
When a version of a package is updated (Hotfix) / a new version is pushed, the crawler is
trigerred. He then must launch the build of the package via the BUILDER
and retrieve the informations about that build.
On success, the crawler will update the Morphux Package Database™.
On failure, the result must be stored too, and send to maintainer.

## Database
The Morphux Package Database™ is the database of all the packages of Morphux.
This database is used by MPM.

# The Build
In order to build a package, the builder must:
- Launch a VM / Container of Vanilla Morphux (Clean install VM)
- Clone the package source into that env
- Launch the package build by following instructions gived by the maintainer
in the package.json file.
- In order to extract the files / binaries installed by the package, a fakeroot
install must be achieved.
- For the build itself, a modified version of MPM must be called.

# Extracting informations
The following informations must be retrieved by the builder:
- Compilation times (Just 'make' and all the commands (./configure, make, etc))
- Installation size (Size after install - Size before install)
- Determine binaries and config files, with path
- Determine wich libraries are static or dynamic
- Make hash for binaries

# Protocol
This documentation will not cover the entirety of the final protocol, just a
quick overview.

A Protocol must be defined in order for the different services to talk together.
The protocol of the builder is a simple one, because the actions are limited:

- Build a package
- Start VM
- Stop VM
- Sanitize
- Launch a new installation on a VM

The builder must execute the requested action, and then return a response.
This Protocol can be a Text one, built on top of TCP.

# Performance
In order to gain performance, the VMs must be up whenever it's possible.
However, the environment must stay Vanilla, so the builder must clean the installed file
(and the dependencies) after a build.
The builder must force a Sanitize of a VM if required manually, or if the builder
requires it.
In order to Sanitize a VM, a clean Install of Morphux Vanilla must be kept somewhere,
and this install must be copied on the new VM.
The clean install is generated via the associated command, in the protocol.

# Code
- Threading
- All test
- Calling the mpm binary | using the mpm library
- Non blocking sockets
