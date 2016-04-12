

Parse.Cloud.afterSave("Artwork", function (request, response)
{
   console.log('\n\n\nAfterSave -- Artwork\n\n');

   Parse.Cloud.useMasterKey();
   var _ = require('underscore.js');
   var Image = require("parse-image");

   var resize = Parse.Cloud.httpRequest({url: request.object.get("file").url()})

       .then(function(response) {
         var promise = Parse.Promise.as();

         promise = promise.then(function() {
           // Create an Image from the data.
           var image = new Image();
           return image.setData(response.buffer);
         })
         // Crop the image.
         .then(function(image) {
            console.log("Scaling Image");
            var max = 1800;
            var width = image.width();
            var height = image.height();
            if(width > height)
            {
              if(width > max) {
                height *= max / width;
                width = max;
              }
            }
            else if(height > width) {
              if(height > max) {
                width *= max / height;
                height = max;
              }
            }
            else if (height == width) {
              if(height > max) {
                width  = max;
                height = max;
              }
            }
            else {
              console.log('Skipping Scale');
            }
            console.log("..scaled to " + width + " x " + height);
            return image.scale({
                   width: width,
                   height: height
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

       return promise;
     });


   // Wrap It Up
   resize.then(function(result)
   {
     console.log('Success!' + result + '\n\n');
     response.success(result);
   },
   function (error)
   {
    console.log('Got Error ' + error.code + ' : ' + error.message + '\n\n');
    response.error(error);
  });

}); /* eom */
