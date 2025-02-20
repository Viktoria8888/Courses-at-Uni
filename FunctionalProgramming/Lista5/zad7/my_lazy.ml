
type 'a tree_way = 
  | Unit of (unit -> 'a)
  | Val of 'a
  | Eval 
and 'a my_lazy= 'a tree_way ref 

let from_fun (f: unit->'a): ('a my_lazy) = ref (Unit f)

let force (x: 'a my_lazy) =
  match !x with
  | Unit f -> 
        x := Eval; (*declare that the evaluation is in progress*)
        let v = f () in
        x := Val(v);
        v
  | Val  x -> x
  | Eval -> failwith "force: not evaluated!"

let fix (f: 'a my_lazy -> 'a): 'a my_lazy =
  let start = ref (ref Eval) in
  let ans = ref (Unit(fun () -> f !start )) in
  start := ans ;
  ans

(* start = my_lazy :Eval
ans = my_lazy (Unit(fun ()-> (force !start))); | fix (fun l -> force l)
force !start -> raises the error *)
type 'a node = 
  | Nil
  | Cons of 'a * ('a llist)
and 'a llist = ('a node) my_lazy

let head (ll : 'a llist) : 'a = 
  match (force ll) with
  | Nil -> failwith "empty!"
  | Cons(x, _) -> x

let tail (ll : 'a llist) : 'a llist = 
  match (force ll) with
  | Nil -> failwith "empty!"
  | Cons(_, x) -> x

let stream_of_ones = fix (fun stream_of_ones -> Cons(1, stream_of_ones))

(* task 8 *)
(* let rec filter (p : 'a -> bool) (xs : 'a llist) : 'a llist = 
  match force xs with
  | Cons(x, xs) when p x -> Cons(x, Unit(fun () -> filter p xs))
  | Cons(_, xs) -> Unit(fun () -> filter p xs) *)

(* let rec take_while p xs = fun () ->
  match xs () with
  | Cons(x, xs) when p x -> Cons(x, take_while p xs)
  | _ -> Nil

let rec for_all p xs =
  match xs () with
  | Nil -> true
  | Cons(x, xs) -> p x && for_all p xs

let rec nth n xs =
  match n, xs () with
  | _, Nil -> failwith "nth"
  | 0, Cons(x, _) -> x
  | _, Cons(_, xs) -> nth (n-1) xs

let rec primes () =
  let is_prime n =
    primes
    |> take_while (fun p -> p * p <= n)
    |> for_all (fun p -> n mod p <> 0)
  in
  Cons(2, filter is_prime (nats_from 3)) *)


let rec interleave s1 s2 = fun () -> match(s1 (), s2 ()) with
  | (Seq.Nil, Seq.Cons(x, xs)) | (Seq.Cons(x, xs), Seq.Nil) -> Seq.Cons(x, xs)
  | Seq.Nil, Seq.Nil -> Seq.Nil
  | Seq.Cons(x, xs), Seq.Cons(y, ys) -> 
    Seq.Cons(x, fun () -> Seq.Cons(y, (interleave xs ys)))