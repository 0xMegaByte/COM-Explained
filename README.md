# COM Explained

Simple server-client based on COM objects

## Description

I created this repo to give a coherent understanding of what COM objects are and how to use it in a server-client context.


In this project we will build a remote controlled spaceship from the ground up using COM.


## What is...?

### [COM (Component Object Model)](https://docs.microsoft.com/en-us/windows/win32/com/component-object-model--com--portal)
COM is a system for creating binary software components that can interact with.\
Each component can be used by other binaries at the same time without any interruption.

In the spaceship this is the standard protocol that each component utilize in order to interact with other components in the spaceship's system.


### [IDL (Interface Definitions Language)](https://docs.microsoft.com/en-us/windows/win32/midl/interface-definition-idl-file)
IDL is a descriptive language to describe interfaces being implemented by objects.


files contains the building blocks of our spaceship.\
It contains the spaceship's interfaces such as engine, flight status system and their functions.

### [TLB (Type Libraries)](https://docs.microsoft.com/en-us/windows/win32/midl/com-dcom-and-type-libraries)

A binary file that stores info about COM object's properties and  methods in a form that is accessible to other applications at runtime. Using a type library, an application or browser can determine which interfaces an object supports, and invoke an object's interface methods.

&nbsp;

---



## Getting Started

### Dependencies

* [Windows 10 SDK](https://developer.microsoft.com/en-us/windows/downloads/windows-sdk/)
* [Visual Studio 2022](https://visualstudio.microsoft.com/vs/whatsnew/)

### Clone Repository
open ```Developer Command Prompt for VS 2022.exe``` and clone the repository:
 ```
 git clone https://github.com/0xMegaByte/COM-Explained.git
 cd COM-Explained
 cd IDL
 ```

---

### IDL Setup
* Open and edit ```SpaceshipLocalServer_TypeInfo.idl```\
Using ```Developer Command Prompt for VS 2022.exe``` do the following:
* For every UUID in the file, generate your own to avoid UUID collision
    * Enter ```uuidgen```
    * Copy the new generated UUID and replace it with the one it the file
    ```
    [
	    object,
	    uuid(<new_generated_uuid>),
	    oleautomation,
	    helpstring("Gets spaceship's status info")
    ]
    ```
After all UUIDs replaced and saved, it's time to compile the IDL file.\
Run:
```
midl.exe SpaceshipLocalServer_TypeInfo.idl
```
New files added to the IDl folder:
```
SpaceshipLocalServer_TypeInfo.h
SpaceshipLocalServer_TypeInfo.tlb
SpaceshipLocalServer_TypeInfo_i.c
SpaceshipLocalServer_TypeInfo_p.c
dlldata.c
```
These files are crucial for the client and server to compile successfully.

---
### Compile client and server solutions

* Navigate to ```COM-Explained\COMClient-Sample``` and open the solution with Visual studio 2022
>NOTE: if you open it with a lower version of visual studio, you might need to re-target the solution.

* build the solution.

Repeat the process with ```COM-Explained\COMServer-Sample```.

---


### Server Registration
Navigate to ```COM-Explained\Registry``` folder and edit the file as the following:
* Copy the Spaceship ```coclass``` generated UUID (found in the IDL file) and replace ```<GENERATED_COCLASS_UUID>``` with it.
* Replace ```<PATH>``` with the path of the compiled ```COMServer-Sample.exe```
* Save and double click ```RegisterServer.reg``` to register these values in your registry

Upon registration, the spaceship coclass UUID is now associated with the ```COMServer-Sample.exe``` path.
When called, the ```COMServer-Sample.exe``` executes and acts as a server.

---

### Executing program

After a successful server registration, we execute the client.
* Navigate to the compiled COMClient-Example.exe and run it through command-line to capture the command-line output.


---

### Debugging

#### Server:
Instead letting the server to be executed when called, we can run it through ```Visual Studio 2022``` and set breakpoints wherever we want in order to follow the command chain when a certain functionality called.\
Open ```COM-Explained\COMServer-Sample\COMServer-Sample.sln```, set breakpoints and run.
A console will be open that will make thing easier to follow.

#### Client:
While the server is running in debug, we can debug the client in another ```Visual Studio 2022``` instance.\
Open ```COM-Explained\COMClient-Sample\COMClient-Sample.sln```, set breakpoint on remote calls and start debugging.\
A console will be open that will make thing easier to follow.

I recommend to put both client and server console next to each other to see the calls connection visually.

---

## Help

### Registration problems

```
Client>> Get spaceship class factory interface...failed!
Client>> ERROR: Class not registered (0x80040154)
```
It means that something went wrong with server registration, double check COMServer-Example.exe path and Spaceship ```coclass``` UUID.

---

## Authors
Matan Shitrit 
[@0xMegaByte](https://twitter.com/0xMegaByte)

## Acknowledgments

 [Building a LOCAL COM Server and Client: A Step by Step Example by liyang yu](https://www.codeproject.com/Articles/8679/Building-a-LOCAL-COM-Server-and-Client-A-Step-by-S)

 [Basics of an IDL file by Sabitha Abraham](https://www.codeproject.com/Articles/19605/Basics-of-an-IDL-file)
