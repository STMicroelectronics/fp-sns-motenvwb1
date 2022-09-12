---
pagetitle: Release Notes for OpenThread Stack
lang: en
---

::: {.row}

::: {.col-sm-12 .col-lg-4}

::: {.card .fluid}

::: {.sectione .dark}

<center>
# <small>Release Notes for</small> OpenThread Stack
Copyright &copy; 2020 STMicroelectronics\
    
[![ST logo](_htmresc/st_logo.png)](https://www.st.com){.logo}
</center>

:::

:::


License
=======

-   The STM32\_WPAN middleware makes the link between the Application
    and the different stacks (BLE /Thread /Mac 802\_15\_4). \
    The directory named core
    (Middlewares\\ST\\STM32\_WPAN\\thread\\openthread\\core)
    contains the wrapper used to control the OpenThread stack from the
    Application.\
    This software module is licensed by ST under Ultimate Liberty
    license SLA0044, the "License"; You may not use this file except in
    compliance with the License. You may obtain a copy of the License
    at:  [SLA0044](http://www.st.com/SLA0044)\
-   The Thread stack running on the STM32WB device is provided by
    OpenThread.\
    The directory named stack
    (Middlewares\\ST\\STM32\_WPAN\\thread\\openthread\\stack) contains
    all the APIs provided by OpenThread.\
    This software module is licensed by ST under BSD 3-Clause license,
    the "License"; You may not use this component except in compliance
    with the License. You may obtain a copy of the License at:
    <https://opensource.org/licenses/BSD-3-Clause>

Thread overview
===============

Thread is an IPV6-based,royalty-free networking protocol for Internet of
Things (Iot). This protocol is mainly used on "smart" home automation
devices to communicate on a local wireless mesh network. Thread uses
6LoWPAN, which in turn uses the IEE 802.15.4 wireless protocol.

The Thread stack contains several layers as shown on the figure below:

[![ThreadLayers
logo](_htmresc/ThreadLayers.png)](https://www.threadgroup.org/){.logo}

OpenThread Stack
================

-   The Thread stack running on the STM32WB device is provided by
    OpenThread and available at :
    <https://github.com/openthread/openthread>

-   OpenThread released by Nest is an open-source implementation of the
    Thread networking protocol. To learn more about this stack, refer
    yourself to the following link: <https://openthread.io>
:::

::: {.col-sm-12 .col-lg-8}
Update History
==============

::: {.collapse}
<input type="checkbox" id="collapse-section2" checked aria-hidden="true">
<label for="collapse-section2" aria-hidden="false">V1.1.0 / 17-November-2020</label>
<div>

## Main Changes

OpenThread version based on commit :

-   SHA-1: 3dbd91aa2b70c7d5cc71b2c465ce3583a13dea79 (tag: **thread-reference-20191113**)

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section1" aria-hidden="true">
<label for="collapse-section1" aria-hidden="false">V1.0.0 / 31-January-2019</label>
<div>

## Initial release

OpenThread version based on commit :

-   SHA1 222acd1362af9f5b58bae9d246fe5492c38e7b14.

-   To support MTD (Minimal Thread Device), on top of above version, the
    following OpenThread commit has been applied: "facd343: \[meshcop\]
    support operational dataset operations for MTD". (This commit is
    mandatory for the support of MTD)

</div>
:::

:::
:::

For complete documentation on STM32WBxx, visit:
\[[www.st.com/stm32wb](http://www.st.com/stm32wb)\]
