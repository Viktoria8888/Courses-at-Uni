type 'a h =
  |Leaf 
  |Node of int * 'a h * int * 'a h
let get_rank h = function
  |Leaf -> 0
  |Node(r,_,_,_) -> r
let empty = Leaf 
let rec is_heap_priority p h = match h with
  | Leaf -> true 
  | Node (_, _, p', _) -> p < p'

let rec is_valid h = match h with
  | Leaf -> true 
  | Node (n, l, v, r) -> 
      (get_rank l) >= (get_rank r) &&
      n = (min (npl l) (npl r)) + 1 &&
      (is_heap_priority p l) && (is_heap_priority p r) &&
      (is_valid l) && (is_valid r)

let make_node v1 v2 x = 
  let r1 = get_rank v1 and r2 = get_rank v2 in
  if r1 >= r2 then Node(v1, x, r2 + 1, v2)
  else  Node(v2, x, r1 + 1, v1)

let rec merge v1 v2 = 
  match v1, v2 with
  | Leaf, v2 -> v2
  | v1, Leaf -> v1
  | Node(v1l,x1,r1,v1r), Node(v2l,x2,r2,v2r) ->
    if x1 < x2 then create v1l (merge v1r v2) x1
    else create v2l (merge v2r v1) x2

let insert v1 x = 
  merge v1 (create empty empty x)

let erasemin v =
  match v with
  | Leaf -> Leaf
  | Node(l,x,len,r) -> merge l r