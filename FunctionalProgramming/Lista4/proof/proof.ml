open Logic
type currassums = (string * formula) list

type proof_tree = 
  | Goal of currassums * formula (*leaf*)
  | Qed of theorem (*leaf*)
  | ImpI of currassums * formula * proof_tree
  | ImpE of currassums * formula * proof_tree * proof_tree
  | BotE of currassums * formula * proof_tree
  

type context = 
| Root 
| CImpELeft  of context * currassums * formula * proof_tree
| CImpERight of context * currassums * formula * proof_tree
| CImpI      of context * currassums * formula
| CBotE      of context * currassums * formula
type zipper = context * proof_tree 

type proof = 
| Compl   of theorem
| Incompl of zipper

let proof g f =
  (Incompl (Root, Goal(g,f)))

let qed = function
  | Compl(thm) -> thm
  | _ -> failwith "not complete"

let goal = function
  | (Compl thm) -> None
  | Incompl(ctx, Goal(assm, f)) -> Some(assm, f)
  
let rec down (ctx, t): zipper: currassums option = 
  match t with
  | Qed(thm) -> None (*no goal found.*)
  | Goal(assms, f) -> Some(assms, f)
  | ImpI(assms, f, pt) -> down CImpI(ctx,assms,f) pt
  | BotE(assms, f, pt) -> down CBotE(ctx,assms, f) pt 
  (* traversing from left to right*)
  | ImpE(assms, f, l, r) -> (*left and right part*)
    let left_goal = down CImpELeft(ctx,assms,f,r) l in 
      match left_goal with
      begin
        | None -> down CImpERight(ctx, assms, f, l) r
        | Some(assms, f) -> Some(assms, f)
      end


let get_prev (f : formula) : formula = 
  match f with
  | Imp(f1, f2) -> f1
  | _           -> failwith "get_prev"

(* move back up the proof tree to combine results from subproofs
 and verify if larger parts of the proof are complete*)
let up (ctx, t) : zipper : proof =
  match t with 
    | Qed(thm1) ->
      begin match ctx with 
        | Root -> Compl(thm1)
        | CImpELeft(ctx, assms, f, rt) -> (*check if the other part of the tree is proved*)
          begin match rt with
            | Qed(thm2) -> Incompl(ctx, Qed(imp_e thm1 thm2))
            | _ -> Incompl(ctx, ImpE(assms, f, t, rt))
          end
        | CImpERight(ctx, assms, f, lt) -> (*check if the other part of the tree is proved*)
          begin match lt with
            | Qed(thm2) -> Incompl(ctx, Qed(imp_e thm1 thm2))
            | _ -> Incompl(ctx, ImpE(assms, f, lt, t))
          end
        | CImpI(ctx, assms, f) -> Incompl(ctx, Qed(imp_i (get_prev f) thm1))
        | CBotE(ctx, assms, f) -> Incompl(Qed(bot_e f thm1))
      end
    | _ -> match ctx with
      | Root -> Incompl(ctx,t)
      | CImpELeft(ctx, assms, f, rt) -> Incompl(ctx, ImpE(assms, f,t,rt))
      | CImpERight(ctx, assms, f, lt) -> Incompl(ctx, ImpE(assms, f,lt,t))
      | CImpI(ctx, assms, f) -> Incompl(ctx, ImpI(assms, f,t))
      | CBotE(ctx, assms, f) -> Incompl(ctx, BotE(assms, f,t))
      



let next pf  =
  match pf with
  | Compl(thm) -> pf
  | Incompl(ctx,pt) ->
    match ctx  with
    | Root ->
      begin match down (ctx, pt) with
        | None -> up (ctx, pt)  (*no goals - finalize the proof. *)
        | Some(ctx, t) -> Incompl(ctx, t)
      end  
    | CImpELeft(ctx, assms, f, rt) -> 
      begin match down CImpERight(ctx, assms, f, pt) rt with
        | None -> up(ctx,pt) |> next
        | Some(ctx,t) -> Incompl(ctx, t)
      end
    | _ -> up(ctx,pt) |> next




let intro name pf =
  match pf with
    | Compl _ -> failwith "intro: complete"
    | Incomp(ctx, pt) ->
      begin match goal pt with
        | None -> failwith "intro: no goal"
        | Some(assm, Imp(psi, fi))-> 
          Incompl(CImpI(ctx, assm, Imp(psi, fi)), Goal((name, psi) :: assm, fi))
        | _ -> failwith "not an implication :("
      end
 
(*psi->psi_next->...->psi_n->fi*)
let elimImp (pf:proof) (psi: formula) = 
  match pf with
    | Compl _ -> failwith "elimImp: complete proof "
    | Incomp(ctx, pt) ->
      begin match goal pf with
        | None -> "elimImp: no goals"
        | Some(assms, psi_next) ->  
          Incomp(CImpELeft(ctx,assms, psi_next, Goal(assms, psi)), 
                 Goal(assms, Imp(psi, psi_next)))
      end
  

let elimImpBottom (pf:proof) =
  match pf with
    | Compl _         -> failwith "elimImpBottom"
    | Incompl(ctx, t) -> 
      match goal pf with
        | None          -> failwith "elimImpBottom"
        | Some(assm, f) -> Incompl(CBotE(ctx, assm, f), Goal(assm, Bottom))




let pp_print_proof fmtr pf =
  match goal pf with
  | None -> Format.pp_print_string fmtr "No more subgoals"
  | Some(g, f) ->
    Format.pp_open_vbox fmtr (-100);
    g |> List.iter (fun (name, f) ->
      Format.pp_print_cut fmtr ();
      Format.pp_open_hbox fmtr ();
      Format.pp_print_string fmtr name;
      Format.pp_print_string fmtr ":";
      Format.pp_print_space fmtr ();
      pp_print_formula fmtr f;
      Format.pp_close_box fmtr ());
    Format.pp_print_cut fmtr ();
    Format.pp_print_string fmtr (String.make 40 '=');
    Format.pp_print_cut fmtr ();
    pp_print_formula fmtr f;
    Format.pp_close_box fmtr ()

