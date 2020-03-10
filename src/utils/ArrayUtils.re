let getOpt = (a, i) =>
  try(Some(a |> Array.get(i))) {
  | Not_found => None
  };

let isEmpty = a =>
  switch (a) {
  | [||] => true
  | _ => false
  };

let isNotEmpty = a => !(a |> isEmpty);
