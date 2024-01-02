![image](https://github.com/JDSherbert/Unreal-Engine-Networked-Sprint-Component/assets/43964243/861c2355-34f5-4261-a6b0-deffb480d7d8)

# Unreal Engine Networked Sprint Component

<!-- Header Start -->
<a href = "https://docs.unrealengine.com/5.3/en-US/"> <img height="40" img width="40" src="https://cdn.simpleicons.org/unrealengine/white"> </a> 
<a href = "https://learn.microsoft.com/en-us/cpp/cpp-language"> <img height="40" img width="40" src="https://cdn.simpleicons.org/c++"> </a>
<img align="right" alt="Stars Badge" src="https://img.shields.io/github/stars/jdsherbert/Unreal-Engine-Networked-Sprint-Component?label=%E2%AD%90"/>
<img align="right" alt="Forks Badge" src="https://img.shields.io/github/forks/jdsherbert/Unreal-Engine-Networked-Sprint-Component?label=%F0%9F%8D%B4"/>
<img align="right" alt="Watchers Badge" src="https://img.shields.io/github/watchers/jdsherbert/Unreal-Engine-Networked-Sprint-Component?label=%F0%9F%91%81%EF%B8%8F"/>
<img align="right" alt="Issues Badge" src="https://img.shields.io/github/issues/jdsherbert/Unreal-Engine-Networked-Sprint-Component?label=%E2%9A%A0%EF%B8%8F"/>
<img align="right" src="https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2FJDSherbert%2FUnreal-Engine-Networked-Sprint-Component%2Fhit-counter%2FREADME&count_bg=%2379C83D&title_bg=%23555555&labelColor=0E1128&title=🔍&style=for-the-badge">
<!-- Header End --> 

-----------------------------------------------------------------------

<a href="https://docs.unrealengine.com/5.3/en-US/"> 
  <img align="left" alt="Unreal Engine Template" src="https://img.shields.io/badge/Unreal%20Engine%20Component-black?style=for-the-badge&logo=unrealengine&logoColor=white&color=black&labelColor=black"> </a>
  
<a href="https://choosealicense.com/licenses/mit/"> 
  <img align="right" alt="License" src="https://img.shields.io/badge/License%20:%20MIT-black?style=for-the-badge&logo=mit&logoColor=white&color=black&labelColor=black"> </a>
  
<br></br>

-----------------------------------------------------------------------
## Overview

This is a replicated sprint component that leverages the enhanced input system for bindings and input action definitions. The sprint component is designed to be easily integrated into your Unreal Engine projects, providing a replicated sprint functionality that synchronizes across the network.

To use this SprintComponent, attach it to an ACharacter.
It works by binding the defined Enhanced Input Action to a function, which modifies the walkspeed value contained within the CharacterMovementComponent (which normally exists by default on ACharacter class objects.) We make sure this occurs across a network by using an RPC (Remote Procedural Call), and the `GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)` function.

Feel free to tweak the values in the script, I've made them easy to find in the .cpp file, inside a namespace!
The code is commented well and transient/autopopulated variables are marked as such.

-----------------------------------------------------------------------

