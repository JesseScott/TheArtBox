Parse.Cloud.define("addUserToRole", function(request, response)
{
	Parse.Cloud.useMasterKey();
	
	var roleQuery = new Parse.Query(Parse.Role);
	roleQuery.equalTo("name", "Moderator");
	roleQuery.first(
	{
		success: function(adminRole)
		{
			var userQuery = new Parse.Query(Parse.User);
			userQuery.equalTo("username", "nsnh");
			userQuery.first(
			{
				success: function(userToAdd)
				{
					adminRole.getUsers().add(userToAdd);
					adminRole.save();
					response.success("successfully added user to administrators");
				},
				error: function(error)
				{
					response.error("error adding user to admin role: " + error.code + " - " + error.message);
				}
			}); 
		},
		error: function(error)
		{
			response.error("error adding user to administrators: " + error.code + "-" + error.message);
		}
	});
});
