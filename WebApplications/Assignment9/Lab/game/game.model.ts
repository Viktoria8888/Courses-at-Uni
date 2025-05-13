export interface Ingredient {
    name: string;
  }
export interface Elixir {
    name: string;
    effect: string;
    sideEffects: string;
    characteristics: string | null;
    time: string | null;
    difficulty: string;
    ingredients: Ingredient[];
    inventors: string[];
    manufacturer: null | string;
  }
export interface Spell {
    name: string;
    incantation: string;
    effect: string;
    canBeVerbal: boolean;
    type: string | null;
    light: string | null;
    creator: string | null;
  }