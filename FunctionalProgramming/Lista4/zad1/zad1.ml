

type nlist2 = 
  | Nil
  | Zero of ('a * 'a) nlist2
  | One  of 'a * ('a * 'a) nlist2
  | Two of ('a * 'a) * ('a * 'a) nlist2
 


let rec cons2 : type a. a -> a nlist -> a nlist =
  fun x xs ->
  match xs with
  | Nil        -> One(x, Nil)
  | Zero xs    -> One(x, xs)
  | One(y, xs) -> Two((x,y) xs)
  | Two((y,z), xs) -> One(x, cons2 (y,z) xs)  


let rec view2 : type a. a nlist -> (a * a nlist) option =
  function
  | Nil        -> None 
  | Zero xs    ->
    begin match view2 xs with
    | None -> None 
    | Some((x, y), xs) -> Some(x, One(y, xs))
    end
  | One(x, xs) -> Some(x, Zero xs) 
  | Two((x,y), xs) -> Some(x, One(y,xs))

  
let rec nth: type a. a nlist -> int -> a =
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
  | Two((x,y),xs) -> if n=0 then x
  else nth (One(y,xs)) (n-1)
