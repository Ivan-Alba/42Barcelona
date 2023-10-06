if (document.cookie != null && document.cookie != "") {
  getCookies();
  console.log("Hay cookies");
} else {
  console.log("No hay cookies");
  var itemId = 0;
}

function findHighestId() {
  let highestId = -1;
  Array.from(document.getElementById("ft_list").childNodes).forEach(node => {
    const id = parseInt(node.id.replace("id", ""), 10);
    if (!isNaN(id) && id > highestId) {
      highestId = id;
    }
  });
  return highestId;
}

// Inicializar itemId en un valor superior en 1 a la ID más alta de las tareas existentes.
itemId = findHighestId() + 1;

function newTask() {
  let description = prompt("Please enter description: ", "New task description");

  if (description != null && description != "") {

    var containerDiv = document.getElementById("ft_list");

    var newDiv = document.createElement("div");
    var label = document.createElement("label");

    label.innerText = description;
    newDiv.appendChild(label);

    //------Style new div --------
    newDiv.id = "id" + itemId;
    itemId++;
    newDiv.style.margin = "auto";
    newDiv.style.marginBottom = "5px";
    newDiv.style.border = "2px solid #000000";
    newDiv.style.borderRadius = "5px";
    newDiv.style.width = "50%";
    newDiv.style.height = "35px";
    newDiv.onclick = function () { deleteTask(newDiv) };

    //Anadimos el objeto recién creado
    containerDiv.appendChild(newDiv);

    //Save task in cookies
    saveCookie(newDiv.id, description, 100);

    //Order nodes
    sortNodes();
  }
}

function deleteTask(div) {
  if (confirm("Do you want to delete task?") == true) {
    deleteCookie(div.id);
    document.getElementById("ft_list").removeChild(div);
  }

}

function sortNodes() {
  var containerDiv = document.getElementById("ft_list");

  //Ordenamos childs según su id
  Array.from(containerDiv.childNodes)
    .sort((a, b) => a.id < b.id ? 1 : -1)
    .forEach(node => containerDiv.appendChild(node));

  Array.from(containerDiv.childNodes)
    .sort((a, b) => a.id < b.id ? 1 : -1)
    .forEach(node => containerDiv.appendChild(node));

}

function saveCookie(name, value, days) {
  const date = new Date();
  date.setTime(date.getTime() + days * 24 * 60 * 60 * 1000);
  let expires = `expires=${date.toUTCString()}`;
  document.cookie = `${name}=${value}; ${expires}; path=/`;
  console.log(`${name}=${value}; ${expires}; path=/`);
  console.log(document.cookie);
}

function deleteCookie(name) {
  saveCookie(name, null, null);
}

function getCookies() {
  const cDecodec = decodeURIComponent(document.cookie);
  const cArray = cDecodec.split("; ");

  cArray.forEach(element => {
    let taskInfo = element.split("=");
    createTaskFromCookie(taskInfo[0], taskInfo[1]);
  });

}

function createTaskFromCookie(id, description) {
  var containerDiv = document.getElementById("ft_list");

  var newDiv = document.createElement("div");
  var label = document.createElement("label");
  label.innerText = description;
  newDiv.appendChild(label);

  newDiv.id = id;

  newDiv.style.margin = "auto";
  newDiv.style.marginBottom = "5px";
  newDiv.style.border = "2px solid #000000";
  newDiv.style.borderRadius = "5px";
  newDiv.style.width = "50%";
  newDiv.style.height = "35px";
  newDiv.onclick = function () { deleteTask(newDiv) };

  //Anadimos el objeto recién creado
  containerDiv.appendChild(newDiv);
  sortNodes();
}