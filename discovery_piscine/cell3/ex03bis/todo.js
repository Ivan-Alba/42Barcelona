$(document).ready(function() {
  if (document.cookie != null && document.cookie != "") {
    getCookies();
    console.log("Hay cookies");
  } else {
    console.log("No hay cookies");
    var itemId = 0;
  }

  //Función que encuentra la ID más alta de entre las task 
  function findHighestId() {
    let highestId = -1;
    $("#ft_list > div").each(function() {
      const id = parseInt(this.id.replace("id", ""), 10);
      if (!isNaN(id) && id > highestId) {
        highestId = id;
      }
    });
    return highestId;
  }

  // Inicializar itemId en un valor superior en 1 a la ID más alta de las tareas existentes.
  var itemId = findHighestId() + 1;

  $("#newTaskButton").click(function() {
    newTask();
  });

  function newTask() {
    let description = prompt("Please enter description:", "New task description");

    if (description != null && description != "") {
      var containerDiv = $("#ft_list");

      var newDiv = $("<div>");
      var label = $("<label>").text(description);

      newDiv.append(label);

      //------Estilo del nuevo div --------
      newDiv.attr("id", "id" + itemId);
      itemId++;
      newDiv.css({
        margin: "auto",
        marginBottom: "5px",
        border: "2px solid #000000",
        borderRadius: "5px",
        width: "50%",
        height: "35px"
      });
      newDiv.click(function() {
        deleteTask(newDiv);
      });

      // Agregamos el objeto recién creado
      containerDiv.append(newDiv);

      // Guardar tarea en cookies
      saveCookie(newDiv.attr("id"), description, 100);

      // Ordenar nodos
      sortNodes();
    }
  }

  function deleteTask(div) {
    if (confirm("Do you want to delete task?")) {
      deleteCookie(div.attr("id"));
      div.remove();
    }
  }

  function sortNodes() {
    var containerDiv = $("#ft_list");

    // Ordenar hijos según su id
    containerDiv.children().sort(function(a, b) {
      return a.id < b.id ? 1 : -1;
    }).appendTo(containerDiv);

    containerDiv.children().sort(function(a, b) {
      return a.id < b.id ? 1 : -1;
    }).appendTo(containerDiv);
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

    cArray.forEach(function(element) {
      let taskInfo = element.split("=");
      createTaskFromCookie(taskInfo[0], taskInfo[1]);
    });
  }

  function createTaskFromCookie(id, description) {
    var containerDiv = $("#ft_list");

    var newDiv = $("<div>");
    var label = $("<label>").text(description);

    newDiv.append(label);

    newDiv.attr("id", id);

    // Estilo del nuevo div
    newDiv.css({
      margin: "auto",
      marginBottom: "5px",
      border: "2px solid #000000",
      borderRadius: "5px",
      width: "50%",
      height: "35px"
    });

    newDiv.click(function() {
      deleteTask(newDiv);
    });

    // Agregamos el objeto recién creado
    containerDiv.append(newDiv);
    sortNodes();
  }
});