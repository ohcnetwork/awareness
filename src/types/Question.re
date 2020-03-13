type t = {
  title: string,
  description: string,
  answers: array(Answer.t),
  hint: option(string),
  imageUrl: option(string),
};
let make = (~title, ~description, ~imageUrl=None, ~answers, ~hint) => {
  {title, description, imageUrl, answers, hint};
};

let title = t => t.title;
let description = t => t.description;
let answers = t => t.answers;
let hint = t => t.hint;
let imageUrl = t => t.imageUrl;

let makeArray = questions => {
  questions
  |> Array.map(a =>
       make(
         ~title=a##title,
         ~description=a##description,
         ~imageUrl=a##imageUrl |> Js.Nullable.toOption,
         ~answers=a##answers |> Answer.makeArray,
         ~hint=a##hint,
       )
     );
};
