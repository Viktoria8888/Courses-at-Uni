(* We define the null path length, npl(X), of any node X to be the length of the shortest path
from X to a node without two children. Thus, the npl of a node with zero or one child is
0, while npl(nullptr) = −1. In the tree in Figure 6.20, the null path lengths are indicated
inside the tree nodes.
Notice that the null path length of any node is 1 more than the minimum of the null
path lengths of its children. This applies to nodes with less than two children because the
null path length of nullptr is −1. *)

type ('a, 'b) view = 
  | HLeaf 
  | HNode of int * ('a,'b) heap * 'a * 'b * ('a,'b) heap
and ('a, 'b) heap = ('a, 'b)  view
let empty = HLeaf
let minheap h = 
  match h with
  | HLeaf -> None
  | HNode(_,_,_,x,_) -> (Some x)
let npl h = match h with
  | HLeaf -> -1 
  | HNode (n, _, _, _, _) -> n

let get_p h = match h with
  | HLeaf -> None
  | HNode (_, _, p, _, _) -> Some p

let rec is_heap_priority p h = match h with
  | HLeaf -> true 
  | HNode (_, _, p', _, _) -> p < p'

let rec is_valid h = match h with
  | HLeaf -> true 
  | HNode (n, l, p, v, r) -> 
      (npl l) >= (npl r) &&
      n = (min (npl l) (npl r)) + 1 &&
      (is_heap_priority p l) && (is_heap_priority p r) &&
      (is_valid l) && (is_valid r)

let make_node l p v r = HNode ((min (npl l) (npl r)) + 1, l, p, v, r)

let rec heap_merge h1 h2 = 
  match (h1, h2) with
  | (HLeaf, HLeaf) -> HLeaf
  | (HLeaf, h2) -> h2
  | (h1, HLeaf) -> h1
  | HNode (n1, l1, p1, v1, r1), HNode (n2,l2, p2, v2, r2)->
      if p1 < p2 then
        make_node l1 p1 v1 (heap_merge r1 h2 )
      else make_node l2 p2 v2 (heap_merge r2 h1 )
        
  
      

let insert h p v = heap_merge h (make_node HLeaf p v HLeaf)
let view heap = heap
let erasemin h =
  match h with
  | HLeaf -> HLeaf
  | HNode(_,l,_,_,r) -> heap_merge l r


(* let create_test_heap () =
  let open LeftHeap in
  let h1_1 = make_node HLeaf 21 21 HLeaf in
  let h1_2 = make_node HLeaf 14 14 HLeaf in
  let h2= make_node HLeaf 8 8 HLeaf in
  let h3 = make_node h1_1 10 10 h1_2 in
  let h4 = make_node h3 3 3 h2 in
  h4
let create_test_heap2 () =
  let open LeftHeap in
  let h1_1 = make_node HLeaf 18 18 HLeaf in
  let h1_2 = make_node HLeaf 7 7 HLeaf in
  let h2= make_node h1_1 12 12 HLeaf in
  let h4 = make_node h2 6 6 h1_2 in
  h4
let () =
  let heap = create_test_heap () in
  let heap2 = create_test_heap2 () in
  assert (LeftHeap.is_valid heap); 
  assert (LeftHeap.is_valid heap2);  *)

  (* let left_child = LeftHeap.get_l heap in
  assert (LeftHeap.get_p left_child = Some 3); 
  assert (LeftHeap.get_v left_child = Some 3); 

  let right_child = LeftHeap.get_r heap in
  assert (LeftHeap.get_p right_child = Some 4); 
  assert (LeftHeap.get_v right_child = Some 4);  *)
