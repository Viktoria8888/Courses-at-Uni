type 'a dllist = 'a dllist_data lazy_t
and 'a dllist_data =
    { prev : 'a dllist;
      elem : 'a;
      next : 'a dllist}

let prev l =  (Lazy.force l).prev
let next l =  (Lazy.force l).next
let elem l =  (Lazy.force l).elem

let singleton x =
  let rec node = lazy { prev = node; elem = x; next = node }
  in node

(* task 5 *)
(* aux return a pair with first node in the constructed list and the tail *)
let rec aux (xs: 'a list) (start: 'a dllist) (ll: 'a dllist):('a dllist * 'a dllist ) =
  match xs with
  | [] -> failwith "aux: empty"
  | [x] -> 
    let node = lazy { prev = ll;
                      elem = x;
                      next = start }
                      in (node, node)
  | x :: xs ->
    let rec res = lazy (aux xs start node) and (*head_node, tail*)
    node = lazy { prev = ll;
                  elem = x;
                  next = fst (Lazy.force res) } in
    let (head_node, tail) = Lazy.force res
    in (node, tail)

let rec of_list (xs: 'a list): ('a dllist) =
  match xs with
    | [] -> failwith "of_list: empty"
    | [x] -> singleton x
    | x :: xs ->
      let rec  res = lazy (aux xs node node) and 
      node = lazy { prev = snd (Lazy.force res); 
                    elem = x;
                    next = fst (Lazy.force res) } in
      node 

let xs = [1;2;3;4;5]
let dll = of_list xs
;;assert((prev dll |> elem) = 5)
;;assert((dll == prev (next dll)) = true)

і
(* task 6 *)

let rec left_from (node : int dllist) : int dllist = 
  let rec new_dll = lazy begin
    {prev = (left_from new_dll); elem = (elem node)-1; next = node}
  end in 
  new_dll

let rec right_from (node : int dllist) : int dllist = 
  let rec new_dll = lazy begin
    {prev = node; elem = (elem node)+1; next = (right_from new_dll)}
  end in 
  new_dll

let integers : int dllist = 
  let rec first = lazy begin
    {prev = (left_from first); elem = 0; next = (right_from first)}
  end in
  first
  

;; assert (elem (next (next (prev (prev integers)))) = 0)
;; assert (integers == (prev (next integers)))
;; assert (integers == (next (prev integers)))