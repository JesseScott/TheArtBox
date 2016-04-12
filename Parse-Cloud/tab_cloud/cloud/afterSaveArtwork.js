

Parse.Cloud.afterSave("Artwork", function (request, response)
{
   console.log('\n\n\nafterSave -- Artwork');

   Parse.Cloud.useMasterKey();

   var _ = require('underscore.js');
   var Image = require("parse-image");

   var artwork = request.object;
   var url = artwork.get("file").url();
   console.log(' URL is ' + url);

   var resize = Parse.Cloud.httpRequest({url: url})
       // Create an Image from the data.
       .then(function(response) {
         var promise = Parse.Promise.as();

         promise = promise.then(function() {
           console.log('Http Request!');
           var image = new Image();
           return image.setData(response.buffer);
         })
         // Crop the image.
         .then(function(image) {
           console.log("Scaling Image");
            var _width = 800, _height = 600;
            _height = Math.floor((image.height() * _width) / image.width());
            console.log("..scale to " + _width + " x " + _height);
            return image.scale({
                   width: _width,
                   height: _height
               });
         })
         // Convert Image to JPEG
         .then(function(image) {
             console.log('Setting Format');
             return image.setFormat("JPEG");
         })
         // Get Data of each image.
         .then(function(image) {
              console.log('Setting Data');
             return image.data();
         })
         // Save the bytes to a new file.
         .then(function(buffer) {
             console.log("Creating File");
             var base64 = buffer.toString("base64");
             var name = "resized.jpg";
             var file = new Parse.File(name, { base64: base64 });
             return file.save();
         })
         // attach the image file to the original object
         .then(function(file) {
              console.log("Saving File");
              request.object.set("file", file);
              return request.object.save();
         });
       console.log('Returning...');
       return promise;
     });


   // Wrap It Up
   resize.then(function(result)
   {
     console.log('Success!');
     response.success();
   },
   function (error)
   {
    console.log('Got Error ' + error.code + ' : ' + error.message);
    response.error(error);
  });

}); /* eom */
