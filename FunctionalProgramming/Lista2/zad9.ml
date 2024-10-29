type 'a clist = { clist : 'z. ('a -> 'z -> 'z) -> 'z -> 'z }
let cnil = {clist = fun f z -> z}

let ccons a xs = { clist = (fun f z -> f a (xs.clist f z)) }
let map g xs = {clist = 
  (fun f z -> xs.clist (fun a z -> f (g a) z) z)}

let append xs ys = { clist = 
  (fun f z -> xs.clist f (ys.clist f z))}

let clist_to_list xs = 
  xs.clist (fun a z -> a :: z) []

let rec clist_of_list xs = 
  match xs with
  | [] -> cnil
  | x :: xs -> {clist = (fun f z -> f x ((clist_of_list xs).clist f z)) }



let mylist = (ccons 1 (ccons 2 (ccons 3 cnil)))
let mylist2 = (ccons 4 (ccons 5 (ccons 6 cnil)))
