
for(let i = 4; i > 0; i--){
    let linha = "";
    for(let k = i; k > 0; k--){
        linha += " ";
    }
    for(let j = i - 1; j < 4; j++){
        linha += "#";
    }
    linha += " ";
    for(let j = i - 1; j < 4; j++){
        linha += "#";
    }
    console.log(linha)
}