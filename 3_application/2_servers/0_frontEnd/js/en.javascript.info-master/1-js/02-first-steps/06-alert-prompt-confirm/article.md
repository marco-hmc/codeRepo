# Interaction: alert, prompt, confirm

## prompt

The function `prompt` accepts two arguments:

```js no-beautify
result = prompt(title, [default]);
```

It shows a modal window with a text message, an input field for the visitor, and the buttons OK/Cancel.

`title`
: The text to show the visitor.


```js run
let test = prompt("Test");
```

So, for prompts to look good in IE, we recommend always providing the second argument:

```js run
let test = prompt("Test", ''); // <-- for IE
```

## confirm

## Summary

We covered 3 browser-specific functions to interact with visitors:

`alert`
: shows a message.

`prompt`
: shows a message asking the user to input text. It returns the text or, if Cancel button or `key:Esc` is clicked, `null`.

`confirm`
: shows a message and waits for the user to press "OK" or "Cancel". It returns `true` for OK and `false` for Cancel/`key:Esc`.

All these methods are modal: they pause script execution and don't allow the visitor to interact with the rest of the page until the window has been dismissed.

There are two limitations shared by all the methods above:

1. The exact location of the modal window is determined by the browser. Usually, it's in the center.
2. The exact look of the window also depends on the browser. We can't modify it.

That is the price for simplicity. There are other ways to show nicer windows and richer interaction with the visitor, but if "bells and whistles" do not matter much, these methods work just fine.
