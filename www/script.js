 function clickCounter() {
            const x = document.getElementById("result");
            if (typeof (Storage) !== "undefined") {
                if (sessionStorage.clickcount) {
                    sessionStorage.clickcount = Number(sessionStorage.clickcount) + 1;
                } else {
                    sessionStorage.clickcount = 1;
                }
                x.innerHTML = "You have clicked the button " + sessionStorage.clickcount + " time(s) in this session!";
            } else {
                x.innerHTML = "Sorry, no Web storage support!";
            }
        }