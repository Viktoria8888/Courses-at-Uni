type 'a nlist =
  | Nil
  | Zero of ('a * 'a) nlist
  | One  of 'a * ('a * 'a) nlist

let rec cons : type a. a -> a nlist -> a nlist =
  fun x xs ->
  match xs with
  | Nil        -> One(x, Nil)
  | Zero xs    -> One(x, xs)
  | One(y, xs) -> Zero(cons (x, y) xs)
(* albo none zwraca, jak lista jest pusta, albo some jesli jest glowa i ogon *)
let rec view : type a. a nlist -> (a * a nlist) option =
  function
  | Nil        -> None 
  | Zero xs    ->
    begin match view xs with
    | None -> None (*cała lista jest pusta, bo jak jest zero i przed zerem znowu dopisac zero, to dalej jest zero*)
    (* jak się odejmuje od zera, to się odejmuje jedynkę od straszych cyfr, a zero się zamienia na jedynkę *)
    | Some((x, y), xs) -> Some(x, One(y, xs))
    end
  | One(x, xs) -> Some(x, Zero xs) (*jak się odejmuje jedynkę od liczby, która ma jedynkę na samym końcu to jedynkę zamieniamy na 0*)

let rec nth : type a. a nlist -> int -> a =
  fun xs n ->
  match xs with
  | Nil -> failwith "nth"
  | Zero xs ->
    let (x, y) = nth xs (n / 2) in
    if n mod 2 = 0 then x
    else y
  | One(x, xs) ->
    if n = 0 then x
    else nth (Zero xs) (n-1)
(* Zero xs  - to juz odjelismy x*)