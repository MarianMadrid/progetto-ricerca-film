const apiKey= '258a8e8afdeff299a5d22448b5d89567';
const searchInput= document.getElementById('searchInput');
const movieResults= document.getElementById('movieResults');

//funz per cercare il film
async function searchMovies(query) {
    const url= `https://api.themoviedb.org/3/search/movie?api_key=${apiKey}&query=${query}`;
    const response= await fetch(url);
    //gestione della risposta
    if(!response.ok){
    console.error('Errore nella richiesta:', response.statusText);
    return;
        }


    const data= await response.json();

    displayMovies(data.results);
    
}
//per visualizzare  i film nel dom
function displayMovies(movies) {
    movieResults.innerHTML= '' //pulisce i risultati precedenti

    movies.forEach(movie => {
        const movieCard= document.createElement('div');
        movieCard.classList.add('movie-card');

        const moviePoster= movie.poster_path
        ? `https://image.tmdb.org/t/p/w500${movie.poster_path}`
        : 'https://via.placeholder.com/200x300';

        movieCard.innerHTML= `
        <img src="${moviePoster}" alt="${movie.title}">
        <h3>${movie.title}</h3>
        <p>Anno: ${movie.release_date ? movie.release_date.split('-')[0]: 'sconosciuto'}</p>`;

        movieResults.appendChild(movieCard);


        
    });
}

searchButton.addEventListener('click', function(){
    const query = searchInput.value.trim();
    if (query.length >2 ) {
        searchMovies(query); //effetua ricerca se ci sono almeno 3 caratteri
    
        
    } else {
        movieResults.innerHTML= ''; //cancella i riusltati se non ce input
        
    }
});

searchInput.addEventListener('input', function(){
    const query= searchInput.ariaValueMax.trim();
    if (query.length >2) {
        searchMovies(query); //ricerca se ci sono 3 caratteri
        
    } else {
        movieResults.innerHTML= ''; //cancella se non ce input
        
    }
})