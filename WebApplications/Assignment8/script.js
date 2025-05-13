document.addEventListener("DOMContentLoaded", () => {
  const pokemonListHtml = document.getElementById("pokemonList");
  const loadingElement = document.getElementById("loading");
  const errorTextElement = document.getElementById("errorText");
  const pokemonContent = document.getElementById("pokemonDetails");

  const preloadImage = async (src) => {
    const img = new Image();
    img.src = src;
    await img.decode();
    return img;
  };

  const fetchData = async () => {
    try {
      loadingElement.style.display = "block"; 
      errorTextElement.style.display = "none"; 

      const postsResponse = await fetch(
        "https://pokeapi.co/api/v2/pokemon-species?limit=151"
      );

      if (!postsResponse.ok) {
        throw new Error("Network response was not ok");
      }

      const data = await postsResponse.json();
      return data.results;
    } catch (error) {
      console.error("Error fetching data:", error);
      errorTextElement.style.display = "block";
      return [];
    } finally {
      loadingElement.style.display = "none"; 
    }
  };

  fetchData().then((pokemonList) => {
    pokemonList.forEach((pokemon) => {
      const newPokemon = document.createElement("li");
      newPokemon.classList.add("pokemonItem");
      newPokemon.textContent = pokemon.name;
      pokemonListHtml.append(newPokemon);
    });
    test_list_size();
  });

  pokemonListHtml.addEventListener("click", (event) => {
    if (event.target.classList.contains("pokemonItem")) {
      const pokemonName = event.target.textContent;
      const pokemonUrl = `https://pokeapi.co/api/v2/pokemon/${pokemonName}`;
      const speciesUrl = `https://pokeapi.co/api/v2/pokemon-species/${pokemonName}`;

      const fetchPokemonDetails = async () => {
        try {
          loadingElement.style.display = "block"; 
          errorTextElement.style.display = "none"; 

        
          const postsResponse = await fetch(pokemonUrl);
          if (!postsResponse.ok) {
            throw new Error("Failed to load Pokémon data");
          }
          const data = await postsResponse.json();
          const pokemonImage = data.sprites.front_default;
          const pokemonTypes = data.types.map((type) => type.type.name);
          const pokemonStats = data.stats;

     
          const speciesResponse = await fetch(speciesUrl);
          if (!speciesResponse.ok) {
            throw new Error("Failed to load Pokémon species data");
          }
          const speciesData = await speciesResponse.json();
          const flavorTextEntry = speciesData.flavor_text_entries.find(
            (entry) => entry.language.name === "en"
          );
          const flavorText = flavorTextEntry ? flavorTextEntry.flavor_text : "No flavor text available.";

   
          await preloadImage(pokemonImage);

   
          pokemonContent.innerHTML = `
            <h2>${pokemonName}</h2>
            <img
              id="pokemonImg"
              class="pokemon-image"
              src="${pokemonImage}"
              alt="${pokemonName}"
            />
            <div id="pokemonTypes" class="types">
              ${pokemonTypes.map((type) => `<span class="type">${type}</span>`).join("")}
            </div>
            <div id="pokemonStats" class="stats">
              ${pokemonStats
                .map(
                  (s) => `<div class="stat">
                              <span>${s.stat.name}</span>
                              <span>${s.base_stat}</span>
                          </div>`
                )
                .join("")}
            </div>
            <div id="pokemonFlavorText" class="flavor-text">
              ${flavorText}
            </div>
          `;
        } catch (error) {
          console.error("Error fetching Pokémon details:", error);
          errorTextElement.style.display = "block"; 
        } finally {
          loadingElement.style.display = "none"; 
        }
      };

      fetchPokemonDetails();
    }
  });
});

const test_list_size = function () {
  console.assert(
    document.querySelectorAll("#pokemonList > li").length == 151,
    "Failed"
  );
};

