let str = React.string;
let logo: string = [%raw "require('../assets/coronaSafeLogo.svg')"];

let json = [%bs.raw {|require("./data.json")|}];
let data = json |> Data.makeData;

let showHome = quiz => {
  <div className="flex flex-wrap md:-mx-3 pt-4">
    {quiz
     |> Array.map(q =>
          <div className="w-full md:w-1/2 pl-3 pr-4 md:px-3 pb-6">
            <div
              className="quiz-component__container border-2 border-gray-800 rounded-lg bg-orange-100 px-4 py-6 md:px-6">
              <h3> {q |> Quiz.title |> str} </h3>
              <p className="pt-1"> {q |> Quiz.description |> str} </p>
              <button
                onClick={_ => ReasonReactRouter.push(q |> Quiz.path)}
                className="btn border-2 border-gray-800 bg-white hover:bg-gray-900 hover:text-white focus:text-white focus:bg-gray-900 button-xl mt-3">
                {q |> Quiz.buttonText |> str}
              </button>
            </div>
          </div>
        )
     |> React.array}
  </div>;
};

let showQuiz = (path, quiz) => {
  switch (quiz |> Quiz.findOpt(path)) {
  | Some(quiz) => <QuizComponent quiz />
  | None => showHome(quiz |> Quiz.default)
  };
};

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();
  let quiz = data |> Data.quiz;
  <div>
    <div className="bg-white w-full border-b border-gray-200">
      <div className="max-w-screen-sm mx-auto">
        <div className="flex justify-between items-end py-4 pl-3 pr-4 md:px-0">
          <a className="w-2/5 md:w-1/3" href="./">
            <img
              className="object-contain"
              src=logo
              title="CoronaSafe: COVID-19 Literacy Mission"
              alt="CoronaSafe Logo: COVID-19 Literacy Mission"
            />
          </a>
          <p className="font-semibold text-xs md:text-base">
            {"COVID-19 Literacy Mission" |> str}
          </p>
        </div>
      </div>
    </div>
    <div className="max-w-screen-sm mx-auto mt-2">
      <div>
        <a
          onClick={_ => ReasonReactRouter.push("english")}
          className="text-lg font-semibold px-2 mr-4 cursor-pointer">
          {"English" |> str}
        </a>
        <a
          onClick={_ => ReasonReactRouter.push("malayalam")}
          className="text-lg font-semibold px-2 mr-4 cursor-pointer">
          {"Malayalam" |> str}
        </a>
      </div>
      {switch (url.path) {
       | ["malayalam"] => showHome(quiz |> Quiz.filterByLang("malayalam"))
       | ["english"] => showHome(quiz |> Quiz.filterByLang("english"))
       | [path] => showQuiz(path, quiz)
       | _ => showHome(quiz |> Quiz.default)
       }}
    </div>
  </div>;
};
