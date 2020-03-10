let getOpt = (a, i) =>
  try(Some(a |> Array.get(i))) {
  | Not_found => None
  };
