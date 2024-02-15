const buttons = document.querySelectorAll(".btn");
let textMessage = document.querySelector(".text-message");

buttons.forEach(button=>{
    button.addEventListener('click', handleButtonClick);
})

function handleButtonClick(event){
    const button = event.currentTarget;
    const message = button.nextElementSibling
    const correct = button.classList.contains("correct");
    const incorrect = button.classList.contains("incorrect");
    if(correct){
        button.classList.add("green");
        message.classList.remove("hide");
        setTimeout(()=>{
            alert("Correct anwser");
            button.classList.remove("green");
            message.classList.add("hide");
        }, 1000);
    }else if (incorrect){
        button.classList.add("red");
        message.classList.remove("hide");
        setTimeout(()=>{
            alert("Incorrect anwser");
            button.classList.remove("red");
            message.classList.add("hide");
        }, 1000);
    }
    }

    function handleInput(){
        const input = document.getElementById("free-anwser").value;
        if(input.toLowerCase() == 'pequim'){
             textMessage.innerText = "Correct!";
             textMessage.style.color = "green";
             setTimeout(()=>{
                textMessage.innerText = "";
             }, 2000)
        }else{
             textMessage.innerText = "Incorrect!";
              textMessage.style.color = "red";
              setTimeout(()=>{
                textMessage.innerText = "";
             }, 2000)
        }
    };

    document.getElementById("free-anwser").addEventListener("keydown", function(event){
        if(event.key === "Enter"){
            event.preventDefault();
            handleInput();
        }
    })