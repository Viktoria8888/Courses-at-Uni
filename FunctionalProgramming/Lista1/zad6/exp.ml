let ctrue a b = if true then a else b

let cfalse a b = if true then b else a

(* Zle *)
(* let cand (f:'a -> 'a -> 'a) (g:'a -> 'a -> 'a) = if (f = ctrue && g = ctrue) then (ctrue:'a -> 'a -> 'a) else cfalse *)

let cand f g = fun a b -> if (f a b) = a && (g a b) = a then a else b;;


(* let cor (f:'a -> 'a -> 'a) (g:'a -> 'a -> 'a) = if (f=ctrue || g=ctrue) then (ctrue:'a -> 'a -> 'a) else cfalse
 *)
let cor f g = fun a b -> if (f a b) = a || (g a b) =a then a else b;;
let cbool_of_bool v = if v then ctrue else cfalse

let  bool_of_cbool v = if (v true false) then true else false;;

(*Rekonstrukcja typów uwzględnia fakt, że funkcje przyjmują dwa różne argumenty*)
bool_of_cbool (cand ctrue  cfalse)
