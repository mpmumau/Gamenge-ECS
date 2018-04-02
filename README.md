# Gamenge::ECS

[![Build Status](https://travis-ci.org/mpmumau/Gamenge-ECS.svg?branch=master)](https://travis-ci.org/mpmumau/Gamenge-ECS)

**Author:** Matthew Mumau <mpmumau@gmail.com>  
**Created:** March 26, 2018  
**License:** MIT License (see LICENSE file for more information)

## Project Overview
Gamenge is a set of a game-related libraries, built in module form, and intended to be used ala-carte. The full suite of components to be included in the Gamenge project will include a 3D rendering engine, and entity-component simulation system, integration with Bullet 3D, an audio interface library and more. 

## ECS Component
This repository contains the source for the "Entity-Component System" (ECS) package of the Gamenge suite.

An "Entity-Component System" is a data structure which may be used to create simulations over time. For example, when used in a game, the ECS as a whole represents the game world: All of the elements of the game (players, monsters, bullets, pickups etc.) are **entities**. Properties of entities (monster color, bullet strength, pickup health amount) are represented as pure-data objects referred to as **components**. Each entity is sent through an iteration of **systems** which perform alterations to the components of entities.

## Dependencies

There are no dependencies for the Gamenge::ECS package.

## Installation

CMake scripts are provided for a standard CMake installation process.

1. Clone this repository to a location of your choice.

2. Make a directory called `build` from the root of that directory.

3. Enter that directory (e.g. `cd build`).

4. Run cmake (e.g. `cmake ..`).

5. Run `make`.

6. Run `make install`.

## Including In Your Project

Simply require the package Gamenge::ECS in your own CMake script.

## Use

To use the ECS module, you will primarily work with an instance of the `Gamenge::ECS` class. Create one like so:

```cpp
using namespace Gamenge;
ECS ecs
```

### Entities

Entities are represented by their identification number (an `EID` value); To work with an entity, you can recall its `EID` value after adding it to the ECS object you created earlier.

```cpp
EID eid = ecs.addEntity();
```

### Components

Components are classes you must first declare and define in your own code. An example component might look something like this:

```cpp
typedef TransformComponent : public Component {
    float x, y, z;
} TransformComponent;
```
To add a component to an entity, you must create a pointer to a `new` component of the type you wish to add. If you wish, you can set initial values for the component upon creation. Then, use the utility function `addComponent` on the ECS object from before to add the component to an entity;

```cpp
TransformComponent *transformComponent = new TransformComponent();
transformComponent->x = 12.51f;
transformComponent->y = 16.12f;

ecs.addComponent(eid, Mask(YOUR_MASK_VALUE), transformComponent);
```

Management of components on the heap is handled by the ECS system; no need to delete your components manually (in fact, don't!)

### Masks

`Entities` `Components` and `Systems` use a special type provided by this module called a `Mask`. Masks are fundementally bitsets. Each component should have a unique, 1-bit wide bitmask assigned to them, while systems should be assigned with a Mask value that represents the types of components used by the system. Each entity, in turn, has a Mask representing which components it has. Many of the functions in the ECS interface ask for mask values, which would presumably be defined outside of the ECS itself in your own game logic, depending on what components represent and what types of data systems intend to act upon. examples of masks are shown throughout the included unit tests.

### Systems

Like `Components`, `Systems` are declared and defined within your own code. `Systems` are classes which are required to at least have a function with the following signature:

```cpp
void tick(Nanos, EID, ComponentBundle)
```

For example, you might have a system that looks like this:

```cpp
class MovementSystem : public System {
    MovementSystem() : System(Mask(0x01) | Mask(0x02), 1) {}

    void tick(Nanos, EID, ComponentBundle) {
        // your logic code here...
    }
}
```

The tick function of a `System` will be called for each entity that has components for the given `Mask` set for the system. Note the syntax above for calling the `System` constructor within the constructor for the custom-defined `MovementSystem` class, which sets the defining mask of components for the `System`. 

The second paramter of the `System` constructor refers to the ordering of the system when systems are iterated. An optional third bool parameter can be set to indicate whether or not to also include the `MessagingComponent` in the `ComponentBundle` for the system (more information about Messaging to follow.)

### Component Bundles

`ComponentBundles` are unordered maps which have `Masks` as keys and `Component *` values for a single entity. They are passed to `System` tick functions in order to allow systems to act upon them.

Because `Components` are stored dynamically as pointers to generic `Components` rather than as their derived types, `System` objects must dynamically cast components like so:

```cpp
Component *tmp = componentBundle.at(Mask(0x01));
TransformComponent *transformComponent = dynamic_cast<TransformComponent *>(tmp);
```

### Messages

`Message` objects represent data to-be sent between different entities. For example, if entities are meant to react to collisions, then doing so is only possible by an entity from within one call of a system's tick function to send a message to another entity.

Like `Components` and `Systems` you must define your own message data structures, derived from a provided base structure, `Message`. The first parameter of the `Message` constructor represents the target of the `Message` and the second value is a numerical ID representation of the type of message being sent, as a `MessageType` value;

```cpp
typedef MyMessage : public Message {
    MyMessage(EID eid) : Message(eid, A_TYPE_ID) {};
    unsigned int myData;
}
```

Messages must also be created on the heap and passed as pointers to the main ECS object.

```cpp
MyMessage *myMessage = new MyMessage(targetEid);
ecs.sendMessage(myMessage);
```

Messages are dispatched to each interested System via a provided `MessagingComponent` object. The `MessagingComponent` is a special `Component` which every entity has. Its `Mask` is `Mask(0x00)`, which is a Mask value that no other `Component` may have. 

`System` objects may define whether or not to take data from the `MessagingComponent` via the third parameter of the `System` constructor. If no third parameter is defined, then a `System` will ignore the `MessagingComponent`

Memory for `Messages` is automatically deleted when it is no longer needed. No need to `delete` your newly created messages (in fact, don't!)

## Running the unit tests

From the build directory created during the installation process, run the command `make test` or `make test ARGS="-V"` to run the unit tests manually. They are also run during continuous integration, implemented on the Travis CI service.

## Building the documentation

From the build directory above, run `make doc` to build the automated HTML documentation, which will then be located in the `doc` directory from the project root.

## More Information

Consult the documents in the `docs` folder for detailed information about the use of the above functions, and more. Reading the `test` source files is also a good way to see examples of potential implementations of the ECS data structure.

## License

This project is released under the MIT license.