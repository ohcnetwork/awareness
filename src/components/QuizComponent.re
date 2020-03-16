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
           <div className="rounded-lg overflow-hidden">
             <img className="w-full" src />
           </div>
         | None => React.null
         }}
      </div>
    </div>
  | None => React.null
  };
};

let showQuestion = (quiz, question, setState, state, totalQuestions) => {
  <div className="pt-4 pb-6 pl-3 pr-4 md:px-0">
    <div
      className="quiz-component__container border-2 border-gray-800 rounded-lg bg-orange-100 px-6 py-6 md:px-10">
      <div
        className="inline-flex leading-tight text-sm text-orange-800 font-semibold bg-orange-200 py-1 px-1 rounded">
        <p className="mr-1">
          {(state.currentQuestionIndex + 1 |> string_of_int)
           ++ " of "
           ++ (totalQuestions |> string_of_int)
           ++ " -"
           |> str}
        </p>
        <p> {quiz |> Quiz.title |> str} </p>
      </div>
      <h1 className="font-bold pt-1 pb-2 leading-tight break-words">
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

let showSuccess = quiz => {
  <div className="px-3 md:px-0 py-4 ">
    <div
      className="quiz-component__container border-2 border-gray-800 rounded-lg bg-orange-100 px-6 py-6 md:px-10">
      <h2 className="text-green-600 leading-tight">
        {quiz |> Quiz.successMessage |> str}
      </h2>
      <a
        href={quiz |> Quiz.readMore}
        target="_blank"
        className="btn border-2 border-gray-800 bg-white hover:bg-gray-900 hover:text-white focus:text-white focus:bg-gray-900 button-xl mt-3">
        {"Read More" |> str}
      </a>
    </div>
    <button
      onClick={_ => ReasonReactRouter.push("/")}
      className="btn border-2 border-gray-800 bg-white hover:bg-gray-900 hover:text-white focus:text-white focus:bg-gray-900 button-xl mt-10">
      <span className="mr-1">
        <svg
          className="w-4"
          xmlns="http://www.w3.org/2000/svg"
          viewBox="0 0 24 24">
          <path
            fill="currentColor"
            d="M23.6 10.12L20.9 8l-8.27-6.46a1 1 0 0 0-1.24 0L3.14 8 .4 10.12a1 1 0 0 0-.18 1.41 1 1 0 0 0 .8.39 1 1 0 0 0 .61-.22l1.13-.88v9a2.84 2.84 0 0 0 2.84 2.84h4.67V12.5h3.48v10.16h4.67a2.84 2.84 0 0 0 2.84-2.84v-9l1.13.88a1 1 0 0 0 .61.22 1 1 0 0 0 .8-.39 1 1 0 0 0-.18-1.42zm-4.37 9.7a.83.83 0 0 1-.83.83h-2.66V11.5a1 1 0 0 0-1-1h-5.5a1 1 0 0 0-1 1v9.16H5.6a.83.83 0 0 1-.83-.83V9.25l3.5-2.74L12 3.6l3.6 2.8 3.63 2.83z"
          />
        </svg>
      </span>
      {"Home" |> str}
    </button>
  </div>;
};

let showQuiz = (quiz, questions, setState, state) => {
  let totalQuestions = questions |> Array.length;
  let currentQuestion =
    questions |> ArrayUtils.getOpt(state.currentQuestionIndex);
  let isLastQuestion = !(state.currentQuestionIndex < totalQuestions - 1);

  <div>
    <div>
      {switch (currentQuestion) {
       | Some(question) =>
         showQuestion(quiz, question, setState, state, totalQuestions)
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
                 <span className="ml-2">
                   <svg
                     className="w-5"
                     xmlns="http://www.w3.org/2000/svg"
                     viewBox="0 0 24 24">
                     <path
                       fill="currentColor"
                       d="M19.92 12.38a1 1 0 0 0 0-.76 1 1 0 0 0-.21-.33l-7-7a1 1 0 0 0-1.42 1.42l5.3 5.3H5a1 1 0 0 0 0 2h11.6l-5.3 5.3a1 1 0 1 0 1.42 1.42l7-7a1 1 0 0 0 .21-.33z"
                     />
                   </svg>
                 </span>
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

  <div>
    {switch (state.page) {
     | Quiz => showQuiz(quiz, questions, setState, state)
     | Complete => showSuccess(quiz)
     }}
  </div>;
};
