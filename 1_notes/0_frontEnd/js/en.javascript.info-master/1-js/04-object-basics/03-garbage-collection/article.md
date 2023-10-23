# Garbage collection

## Reachability

Simply put, "reachable" values are those that are accessible or usable somehow. 
They are guaranteed to be stored in memory.

1. There's a base set of inherently reachable values, that cannot be deleted for obvious reasons.

    - The currently executing function, its local variables and parameters.
    - Other functions on the current chain of nested calls, their local variables and parameters.
    - Global variables.
    - (there are some other, internal ones as well)

    These values are called *roots*.

2. Any other value is considered reachable if it's reachable from a root by a reference or by a chain of references.

    For instance, if there's an object in a global variable, and that object has a property referencing another object, *that* object is considered reachable. And those that it references are also reachable. Detailed examples to follow.

There's a background process in the JavaScript engine that is called [garbage collector](https://en.wikipedia.org/wiki/Garbage_collection_(computer_science)). It monitors all objects and removes those that have become unreachable.

## A simple example

```js
// user has a reference to the object
let user = {
  name: "John"
};
```

![](memory-user-john.svg)

The global variable `"user"` references the object `{name: "John"}` (we'll call it John for brevity). The `"name"` property of John stores a primitive, so it's painted inside the object.


```js
user = null;
```

![](memory-user-john-lost.svg)

## Two references

Now let's imagine we copied the reference from `user` to `admin`:

```js
// user has a reference to the object
let user = {
  name: "John"
};

*!*
let admin = user;
*/!*
```

![](memory-user-john-admin.svg)

Now if we do the same:
```js
user = null;
```

...Then the object is still reachable via `admin` global variable, so it must stay in memory. If we overwrite `admin` too, then it can be removed.

## Interlinked objects

```js
function marry(man, woman) {
  woman.husband = man;
  man.wife = woman;

  return {
    father: man,
    mother: woman
  }
}

let family = marry({
  name: "John"
}, {
  name: "Ann"
});
```

The resulting memory structure:

![](family.svg)

As of now, all objects are reachable.

Now let's remove two references:

```js
delete family.father;
delete family.mother.husband;
```

![](family-delete-refs.svg)

It's not enough to delete only one of these two references, because all objects would still be reachable.

![](family-no-father.svg)

Outgoing references do not matter. Only incoming ones can make an object reachable. So, John is now unreachable and will be removed from the memory with all its data that also became unaccessible.

After garbage collection:

![](family-no-father-2.svg)

## Unreachable island


```js
family = null;
```

![](family-no-family.svg)

## Internal algorithms

The basic garbage collection algorithm is called "mark-and-sweep".

The following "garbage collection" steps are regularly performed:

- The garbage collector takes roots and "marks" (remembers) them.
- Then it visits and "marks" all references from them.
- Then it visits marked objects and marks *their* references. All visited objects are remembered, so as not to visit the same object twice in the future.
- ...And so on until every reachable (from the roots) references are visited.
- All objects except marked ones are removed.

For instance, let our object structure look like this:

![](garbage-collection-1.svg)

We can clearly see an "unreachable island" to the right side. Now let's see how "mark-and-sweep" garbage collector deals with it.

The first step marks the roots:

![](garbage-collection-2.svg)

Then we follow their references and mark referenced objects:

![](garbage-collection-3.svg)

...And continue to follow further references, while possible:

![](garbage-collection-4.svg)

Now the objects that could not be visited in the process are considered unreachable and will be removed:

![](garbage-collection-5.svg)

We can also imagine the process as spilling a huge bucket of paint from the roots, that flows through all references and marks all reachable objects. 

Some of the optimizations:

- **Generational collection** -- objects are split into two sets: "new ones" and "old ones". 
- **Incremental collection** -- if there are many objects, and we try to walk and mark the whole object set at once, it may take some time and introduce visible delays in the execution. So the engine splits the whole set of existing objects into multiple parts. That requires some extra bookkeeping between them to track changes, but we get many tiny delays instead of a big one.
- **Idle-time collection** -- the garbage collector tries to run only while the CPU is idle, to reduce the possible effect on the execution.

## Summary

- Garbage collection is performed automatically. We cannot force or prevent it.
- Objects are retained in memory while they are reachable.
- Being referenced is not the same as being reachable (from a root): a pack of interlinked objects can become unreachable as a whole, as we've seen in the example above.

If you are familiar with low-level programming, more detailed information about V8's garbage collector is in the article [A tour of V8: Garbage Collection](https://jayconrod.com/posts/55/a-tour-of-v8-garbage-collection).

The [V8 blog](https://v8.dev/) also publishes articles about changes in memory management from time to time. Naturally, to learn more about garbage collection, you'd better prepare by learning about V8 internals in general and read the blog of [Vyacheslav Egorov](https://mrale.ph) who worked as one of the V8 engineers. I'm saying: "V8", because it is best covered by articles on the internet. For other engines, many approaches are similar, but garbage collection differs in many aspects.

