let str = React.string;
[%bs.raw {|require("./Home.css")|}];
let logo: string = [%raw "require('../assets/coronaSafeLogo.svg')"];
let github_logo: string = [%raw "require('../assets/github.svg')"];

let json = [%bs.raw {|require("./data.json")|}];
let data = json |> Data.makeData;

let showHome = quiz => {
  <div className="flex flex-wrap md:-mx-3 pt-4">
    {quiz
     |> Array.map(q =>
          <div className="w-full md:w-1/2 pl-3 pr-4 md:px-3 pb-6">
            <div
              className="home__container flex flex-col justify-between h-auto md:h-full border-2 border-gray-800 rounded-lg bg-orange-100 px-4 py-6 md:px-6">
              <div>
                <h3 className="leading-tight"> {q |> Quiz.title |> str} </h3>
                <p className="pt-1 leading-snug">
                  {q |> Quiz.description |> str}
                </p>
              </div>
              <div>
                <button
                  onClick={_ =>
                    ReasonReactRouter.push((q |> Quiz.path) ++ "/1")
                  }
                  className="btn w-auto border-2 border-gray-800 bg-white hover:bg-gray-900 hover:text-white focus:text-white focus:bg-gray-900 button-xl mt-4 md:mt-5">
                  {q |> Quiz.buttonText |> str}
                </button>
              </div>
            </div>
          </div>
        )
     |> React.array}
  </div>;
};

let showQuiz = (path, quiz, questionNoStr) => {
  let questionNo = Url.Quiz.parse(questionNoStr);
  switch (quiz |> Quiz.findOpt(path), questionNo) {
  | (Some(quiz), Some(questionNo)) =>
    <QuizComponent quiz baseUrl=path questionNo />
  | _ => showHome(quiz |> Quiz.default)
  };
};

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();
  let quiz = data |> Data.quiz;
  <div className="main">
    /* Header */

      <div className="bg-white w-full border-b border-gray-200">
        <div className="max-w-screen-sm mx-auto">
          <div
            className="flex justify-between items-end py-4 pl-3 pr-4 md:px-0">
            <a className="w-2/5 md:w-1/3" href="/">
              <img
                className="object-contain"
                src=logo
                title="CoronaSafe: COVID-19 Literacy Mission"
                alt="CoronaSafe Logo: COVID-19 Literacy Mission"
              />
            </a>
            <a
              href="https://www.coronasafe.in/"
              className="font-semibold text-xs md:text-base">
              {"COVID-19 Literacy Mission" |> str}
            </a>
          </div>
        </div>
      </div>
      /* Quiz cards */
      <div className="max-w-screen-sm mx-auto mt-4">
        <div className="text-gray-700 text-sm select-none px-3 md:px-0">
          <a
            onClick={_ => ReasonReactRouter.replace("/english")}
            className="home-langualge-filter__link hover:text-gray-900 hover:border-gray-900 ">
            {"English" |> str}
          </a>
          <a
            onClick={_ => ReasonReactRouter.replace("/malayalam")}
            className="home-langualge-filter__link hover:text-gray-900 hover:border-gray-900 ">
            {{j|മലയാളം|j} |> str}
          </a>
          <a
            onClick={_ => ReasonReactRouter.replace("/french")}
            className="home-langualge-filter__link hover:text-gray-900 hover:border-gray-900 ">
            {{j|Français|j} |> str}
          </a>
          <a
            onClick={_ => ReasonReactRouter.replace("/urdu")}
            className="home-langualge-filter__link hover:text-gray-900 hover:border-gray-900 ">
            {{j|اردو|j} |> str}
          </a>
          <a
            onClick={_ => ReasonReactRouter.replace("/kannada")}
            className="home-langualge-filter__link hover:text-gray-900 hover:border-gray-900 ">
            {{j|ಕನ್ನಡ|j} |> str}
          </a>
        </div>
        {switch (url.path) {
         | ["malayalam"] => showHome(quiz |> Quiz.filterByLang("malayalam"))
         | ["english"] => showHome(quiz |> Quiz.filterByLang("english"))
         | ["french"] => showHome(quiz |> Quiz.filterByLang("french"))
         | ["urdu"] => showHome(quiz |> Quiz.filterByLang("urdu"))
         | ["kannada"] => showHome(quiz |> Quiz.filterByLang("kannada"))
         | [baseUrl, questionNo] => showQuiz(baseUrl, quiz, questionNo)
         | _ => showHome(quiz |> Quiz.default)
         }}
      </div>
      /* Footer */
      <footer className="bg-white w-full border-b border-gray-200 mt-auto">
        <div className="max-w-screen-sm mx-auto">
          <div
            className="flex justify-center items-center py-4 pl-3 pr-4 md:px-0">
            <a
              href="https://github.com/coronasafe/awareness"
              className="font-semibold text-xs md:text-base">
              {"A quiz based app for staying safe in COVID 19 Outbreak" |> str}
            </a>
            <a className="" href="https://github.com/coronasafe/awareness">
              <img
                className="object-contain github_svg ml-3 w-5"
                src=github_logo
                title="Coronasafe  Awareness (Github)"
                alt="CoronaSafe Awareness (Github)"
              />
            </a>
          </div>
        </div>
      </footer>
    </div>;
};
