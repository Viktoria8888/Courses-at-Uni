type 'a tree =
  | Leaf
  | Node of ('a lazy_tree) * 'a * ('a lazy_tree)
and 'a lazy_tree = ('a tree) Lazy.t

let rec frac_tree ((a,b), (c,d))= 
  let root = (a + c), (b + d) in
  let left = lazy (frac_tree ((a,b),root)) in
  let right = lazy (frac_tree (root, (c,d))) in
  (Node(left, root, right))

let t = frac_tree ((0,1), (1,0))

let get_root = function Node(l,v,r) -> v | Leaf -> failwith "leaf"

let get_left = function Node(l,v,r) -> Lazy.force l | Leaf -> failwith "leaf"

let get_right = function Node(l,v,r) -> Lazy.force r | Leaf -> failwith "leaf"
          (* 1/1 -> 1/2, 2/1 *)
(* 1/2 -> 1/3 , 2/3*)    (*2/1 -> 3/2, 3/1*)

(* task 4 *)

(* also works but less clear *)
(* let rec tree_to_seq t = fun () ->  
match t with
| Leaf -> Seq.Nil
| Node (l, v, r) -> 
  let left = fun () -> (tree_to_seq (Lazy.force l)) () in
  let right = fun () -> (tree_to_seq (Lazy.force r)) () in
    Seq.Cons(v, Seq.interleave left right)
         *)

let rec tree_to_seq t = 
match t with
  | Leaf -> Seq.empty
  | Node (l, v, r) -> 
    let left = fun () -> (tree_to_seq (Lazy.force l)) () in
    let right = fun () -> (tree_to_seq (Lazy.force r)) () in
      fun () -> Seq.Cons(v, Seq.interleave left right)
                 
let s1 = tree_to_seq t;;
(* 
# #use "zad3.ml";;
# let s1 = tree_to_seq t;;
val s1 : unit -> (int * int) Seq.node = <fun>
# s1 ();;
- : (int * int) Seq.node = Seq.Cons ((1, 1), <fun>)
# Seq.take 10 s1 |> List.of_seq;;
- : (int * int) list =
[(1, 1); (1, 2); (2, 1); (1, 3); (3, 2); (2, 3); (3, 1); (1, 4); (4, 3);
 (3, 5)]
# #utop_stash "zad3.ml";;

 *)