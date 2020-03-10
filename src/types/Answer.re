type t = {
  title: string,
  description: string,
  imageUrl: option(string),
  youtubeUrl: option(string),
  correctAnswer: bool,
};

let make =
    (~title, ~description, ~imageUrl=None, ~youtubeUrl=None, ~correctAnswer) => {
  {title, description, imageUrl, youtubeUrl, correctAnswer};
};

let title = t => t.title;
let description = t => t.description;
let youtubeUrl = t => t.youtubeUrl;
let imageUrl = t => t.imageUrl;
let correctAnswer = t => t.correctAnswer;

let makeArray = answers => {
  answers
  |> Array.map(a =>
       make(
         ~title=a##title,
         ~description=a##description,
         ~imageUrl=a##imageUrl,
         ~youtubeUrl=a##youtubeUrl,
         ~correctAnswer=a##correctAnswer,
       )
     );
};
