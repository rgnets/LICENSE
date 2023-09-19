# RG Nets LICENSE Information
This repository contains information pertaining the the rXg license and related open source software licenses


# rXg Software License
COPYRIGHT AND LICENSE for rXg Software

    Copyright (c) 2007-2023 RG Nets, Inc. All rights reserved.

    THIS IS UNPUBLISHED PROPRIETARY
    SOURCE CODE OF RG NETS INC.

    The copyright notice above does not evidence any
    actual or intended publication of such source code.

    Possession of this software must be accompanied by a valid
    license agreement with RG Nets, Inc.

# Redistributed Open-Source Software Licenses
The rXg utilizes a collection of freely available open-source software that are made available via the
FreeBSD ports repository.  The list of included packages is maintained in the file [FreeBSD-Packages](FreeBSD-Packages)

The list of Node.js packages used is maintained in the file [Node-Packages](Node-Packages)

The list of Ruby Gems (made available via http://rubygems.org) is maintained in the file [Rubygems](Rubygems)

# Patches to Open-Source Software
Some pieces of software have patches applied in order to work around bugs or improve the software.
Where possible, these patches are always submitted upstream to contribute back to the source project.
Where patches are not accepted or desired by the upstream repository, the patches are applied when the
packages are built from source.  These modifications are provided in the [patches](patches) directory.

Note that the rXg codebase is entirely interpreted, and is not statically or dynamically _linked_
against any other Open-Source software.

Other packages in the list of [FreeBSD-Packages](FreeBSD-Packages) which do not have a corresponding
patch directory are redistributed without modification by RG Nets.
