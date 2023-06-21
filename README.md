# 2D Physics Simulator WannaBe

## Features
 - Modular object and attachment based design
 - Customizable behaviours
 - Potential (?)
 - Glitchy circle collisions
 - Questionable collision resolution in general (I had some fun with it)

## Not-yet features
 - Input (feel free to modify main though!)
 - Collisions with non-circles
 - Physics beyond general movement and collisions (like springs, etc.)
 - Physics affecting rotation
 - Proper documentation

## Main modification quick-tutorial
The simulator is based on Objects. These are abstract entities in the world whose characteristics and 
behaviours can be modified by attaching ObjectAttachments to them. These include Rigidbodies (this is the 
component that adds physics), Colliders (CircleColliders only currently, these add collision capabilities),
Shapes (these define how the object will be drawn on screen) and Behaviours (these add custom behaviours 
to objects, which you can implement yourself, or use and combine the ready-made ones (don't place more than 
one behaviour of the same type on the same object though)). Take care to always use 'new' when creating new 
Objects or ObjectAttachments, as they may attempt to automatically delete each other depending on how you use
them. Also, remember that once an ObjectAttachment has been attached to an Object, that attachment is becomes 
the object's responsibility to manage, so don't go deleting pointers to attached attachments. If you want to 
modify or get information about the attachment, use Object's methods to get a reference to it first. And have
a look over the header files before using something, they should hopefully be pretty descriptive.