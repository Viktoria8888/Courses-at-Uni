type var = string

type formula =
  | Top
  | Var of var
  | Not of formula
  | And of formula * formula
(* Env.lookup x to jest to samo co fun cont -> Env.lookup x cont *)
(* beta redukcja: funkcja, która nic nie robi,
 tylko odrazu swój parametr przekazuje innej funkcji jest równoważna tamtej innej funkcji *)

(* Zdefuniujemy funkcję, która odrazu będzie zwracać wartosć *)
module type S = sig
  type ans
  type 'a t (*ukrywamy przed użytkownikiem, że to jest styl kontynuacyjny*)
  (* 'a   - typ wyniku obliczenia 
     'a t - obliczenie w stylu kontunuacyjnym *)

  val return : 'a -> 'a t 
  val bind   : 'a t -> ('a -> 'b t) -> 'b t
  (* bierze obliczenie a potem, funkcj a która będzie czekać na
   wynik pierwszego obliczenia i decydować co z tym robić *)
  val lookup : var -> bool t

  val exists : bool t -> bool
  val forall : bool t -> bool
end

module Env : S = struct
  module VarMap = Map.Make(String)

  type ans = bool VarMap.t -> bool
  type 'a t = ('a -> ans) -> ans


  let return x = fun cont -> cont x
  (* let bind m f cont =
    m (fun x -> f x cont) *)

  (* let bind m f = fun cont ->
    (m (fun x -> f x)) cont *)
  let bind (m: 'a t)  (f: 'a -> 'b t) = 
    fun (cont:'b -> ans) -> m (fun (x: 'a) -> f x cont) (*liczymy f x, chcemy, zeby to obliczenie sie wykonalo*)

  let lookup x cont env =
    match VarMap.find_opt x env with
    | Some b -> cont b env
    | None   ->
      cont true  (VarMap.add x true  env) ||
      cont false (VarMap.add x false env)

  let exists c = c (fun b _ -> b) VarMap.empty
  let forall c = not (exists (fun cont -> c (fun b -> cont (not b))))
end

module F(Env : S) = struct
  let rec eval f =
    match f with
    | Top   -> Env.return true (*fun cont -> cont true: bierzemy kontynuację, zeby odrazu ją zwrócić*)
    | Var x -> Env.lookup x
    | Not f -> Env.bind (eval f) (fun b -> Env.return (not b))
    | And(f1, f2) ->
      Env.bind (eval f1) (fun b ->
      if b then eval f2 (*ogonowe wywolanie f2*)
      else Env.return false)

      (*Env.bind (eval f1) (fun b ->
      if b then Env.bind (eval f2) (fun b-> Env.return b)
      else Env.return false)*)

  let sat   f = Env.exists (eval f)
  let tauto f = Env.forall (eval f)
end
include F(Env)
