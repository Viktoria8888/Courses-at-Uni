type ('a, 'b) view =
    HLeaf
  | HNode of int * ('a, 'b) heap * 'a * 'b * ('a, 'b) heap
and ('a, 'b) heap = ('a, 'b) view
val npl : ('a, 'b) view -> int
val get_p : ('a, 'b) view -> 'a option
val is_heap_priority : 'a -> ('a, 'b) view -> bool
val is_valid : ('a, 'b) heap -> bool
val make_node : ('a, 'b) heap -> 'a -> 'b -> ('a, 'b) heap -> ('a, 'b) view
val heap_merge : ('a, 'b) heap -> ('a, 'b) heap -> ('a, 'b) heap
val insert : ('a, 'b) heap -> 'a -> 'b -> ('a, 'b) heap
val view : 'a -> 'a
val erasemin : ('a, 'b) view -> ('a, 'b) heap
val empty:  ('a, 'b) heap
val minheap: ('a, 'b) heap -> 'b option