let str = React.string;
[%bs.raw {|require("./QuizComponent.css")|}];

type page =
  | Quiz
  | Complete;

type state = {
  page,
  selectedAnswer: option(Answer.t),
  currentQuestionIndex: int,
};

let updateAnswer = (setState, answer, _event) => {
  setState(state => {...state, selectedAnswer: Some(answer)});
};

let showSelectedAnswer = state => {
  switch (state.selectedAnswer) {
  | Some(answer) =>
    <div className="pt-8 md:pt-12">
      <h2
        className={
          "font-bold mb-2 leading-tight "
          ++ (
            answer |> Answer.correctAnswer ? "text-green-600" : "text-red-600"
          )
        }>
        {answer |> Answer.title |> str}
      </h2>
      <div className="pt-1">
        {answer
         |> Answer.description
         |> Array.mapi((index, d) =>
              <p className="text-lg" key={index |> string_of_int}>
                {d |> str}
              </p>
            )
         |> React.array}
      </div>
      <div className="mt-4">
        {switch (answer |> Answer.youtubeUrl) {
         | Some(src) =>
           <div
             className="quiz-component__video-wrapper rounded-lg overflow-hidden border-2 border-gray-700 bg-gray-100">
             <iframe className="w-full" height="auto" src />
           </div>
         | None => React.null
         }}
      </div>
      <div className="mt-4">
        {switch (answer |> Answer.imageUrl) {
         | Some(src) =>
           <div
             className="rounded-lg overflow-hidden">
             <img className="w-full" src />
           </div>
         | None => React.null
         }}
      </div>
    </div>
  | None => React.null
  };
};

let showQuestion = (question, setState, state) => {
  <div className="pt-4 pb-6 pl-3 pr-4 md:px-0">
    <div
      className="quiz-component__container border-2 border-gray-800 rounded-lg bg-orange-100 px-6 py-6 md:px-10">
      <h1 className="font-bold mb-2 leading-tight">
        {question |> Question.title |> str}
      </h1>
      <div>
        {question
         |> Question.answers
         |> Array.map(answer => {
              <div key={answer |> Answer.option}>
                <button
                  className="btn border-2 border-gray-800 bg-white hover:bg-gray-900 hover:text-white focus:text-white focus:bg-gray-900 button-xl mt-3 w-full"
                  onClick={updateAnswer(setState, answer)}>
                  {answer |> Answer.option |> str}
                </button>
              </div>
            })
         |> React.array}
      </div>
    </div>
    <div> {showSelectedAnswer(state)} </div>
  </div>;
};

let nextQuestion = (setState, _event) => {
  setState(state =>
    {
      ...state,
      currentQuestionIndex: state.currentQuestionIndex + 1,
      selectedAnswer: None,
    }
  );
};

let showSucess = quiz => {
  <div className="px-3 md:px-0 py-4 ">
    <div
      className="quiz-component__container border-2 border-gray-800 rounded-lg bg-orange-100 px-6 py-6 md:px-10">
      <h2 className="text-green-600 leading-tight">
        {quiz |> Quiz.successMessage |> str}
      </h2>
      <a
        href={quiz |> Quiz.readMore}
        className="btn border-2 border-gray-800 bg-white hover:bg-gray-900 hover:text-white focus:text-white focus:bg-gray-900 button-xl mt-3 w-full">
        {"Read More" |> str}
      </a>
    </div>
    <button
      onClick={_ => ReasonReactRouter.push("/")}
      className="btn border-2 border-gray-800 bg-white hover:bg-gray-900 hover:text-white focus:text-white focus:bg-gray-900 button-xl mt-10">
      {"Home" |> str}
    </button>
  </div>;
};

let showQuiz = (questions, currentQuestion, setState, state) => {
  let isLastQuestion =
    !(state.currentQuestionIndex < (questions |> Array.length) - 1);

  <div>
    <div>
      {switch (currentQuestion) {
       | Some(question) => showQuestion(question, setState, state)
       | None => React.null
       }}
    </div>
    <div className="max-w-screen-sm mx-auto">
      <div className="px-3 md:px-0 pb-4">
        {switch (state.selectedAnswer) {
         | Some(_) =>
           isLastQuestion
             ? <button
                 onClick={_ => setState(state => {...state, page: Complete})}
                 className="btn border-2 border-green-600 bg-green-500 text-white hover:bg-green-600 hover:text-white focus:text-white focus:bg-green-600 button-xl w-full">
                 {"Complete" |> str}
               </button>
             : <button
                 onClick={nextQuestion(setState)}
                 className="btn border-2 border-gray-800 bg-orange-100 hover:bg-gray-900 hover:text-white focus:text-white focus:bg-gray-900 button-xl w-full">
                 {"Next Question" |> str}
               </button>
         | None => React.null
         }}
      </div>
    </div>
  </div>;
};

[@react.component]
let make = (~quiz) => {
  let (state, setState) =
    React.useState(() =>
      {currentQuestionIndex: 0, selectedAnswer: None, page: Quiz}
    );
  let questions = quiz |> Quiz.questions;
  let currentQuestion =
    questions |> ArrayUtils.getOpt(state.currentQuestionIndex);

  <div>
    {switch (state.page) {
     | Quiz => showQuiz(questions, currentQuestion, setState, state)
     | Complete => showSucess(quiz)
     }}
  </div>;
};
