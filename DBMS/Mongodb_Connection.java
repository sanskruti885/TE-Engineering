package mysql;
import com.mongodb.client.MongoClient; 
import com.mongodb.client.MongoClients; 
import com.mongodb.client.MongoDatabase;
import com.mongodb.client.MongoCollection; 
import com.mongodb.client.result.DeleteResult; 
import com.mongodb.client.result.UpdateResult; 
import org.bson.Document;
import org.bson.conversions.Bson; 
import java.util.Scanner; 
import static com.mongodb.client.model.Filters.eq; 
import static com.mongodb.client.model.Updates.set; 

public class MYSQL_Connectivity{ 
	public static void main(String args[]) 
{ 
		 String connectionString = "mongodb://te31448:te31448@10.10.8.119:27017/?authSource=te31448_db";
				         MongoClient mongoClient = MongoClients.create(connectionString);
				         MongoDatabase database = mongoClient.getDatabase("te31448_db");
				         MongoCollection<Document> collection = database.getCollection("student");

				         System.out.println("Database Connected Successfully!!");

				         Scanner scanner = new Scanner(System.in);

				         boolean running = true;

				         while (running) {
				             System.out.println("\nChoose an option:");
				             System.out.println("1. Insert student");
				             System.out.println("2. Delete student by name");
				             System.out.println("3. Update student marks by name");
				             System.out.println("4. Exit");
				             System.out.print("Enter choice (1-4): ");

				             int choice = -1;
				             if (scanner.hasNextInt()) {
				                 choice = scanner.nextInt();
				                 scanner.nextLine(); // consume newline
				             } else {
				                 System.out.println("Invalid input. Please enter a number between 1 and 4.");
				                 scanner.nextLine(); // consume invalid input
				                 continue;
				             }

				             switch (choice) {
				                 case 1:
				                     // Insert
				                     System.out.print("Enter name: ");
				                     String name = scanner.nextLine();
				                     System.out.print("Enter age: ");
				                     int age = scanner.nextInt();
				                     System.out.print("Enter marks: ");
				                     int marks = scanner.nextInt();



				                     scanner.nextLine(); // consume newline

				                     Document doc = new Document("name", name)
				                             .append("age", age)
				                             .append("marks", marks);

				                     collection.insertOne(doc);
				                     System.out.println("Student inserted.");
				                     break;

				                 case 2:
				                     // Delete by name
				                     System.out.print("Enter name to delete: ");
				                     String delName = scanner.nextLine();

				                     DeleteResult deleteResult = collection.deleteOne(eq("name", 
				 delName));
				                     if (deleteResult.getDeletedCount() > 0) {
				                         System.out.println("Student deleted successfully.");
				                     } else {
				                         System.out.println("No student found with that name.");
				                     }
				                     break;

				                 case 3:
				                     // Update marks by name
				                     System.out.print("Enter name to update marks: ");
				                     String updateName = scanner.nextLine();
				                     System.out.print("Enter new marks: ");
				                     int newMarks = scanner.nextInt();
				                     scanner.nextLine(); // consume newline

				                     Bson filter = eq("name", updateName);
				                     Bson updateOperation = set("marks", newMarks);

				                     UpdateResult updateResult = collection.updateOne(filter, 
				 updateOperation);
				                     if (updateResult.getMatchedCount() > 0) {
				                         System.out.println("Student marks updated.");
				                     } else {
				                         System.out.println("No student found with that name.");
				                     }
				                     break;

				                 case 4:
				                     running = false;
				                     System.out.println("Exiting program.");
				                     break;

				                 default:
				                     System.out.println("Invalid choice. Please select between 1 and 4.");
				                     break;
				             }

				             // Display all documents after each operation (except exit)
				             if (running) {
				                 System.out.println("\nAll students in collection:");



				                 for (Document d : collection.find()) {
				                     System.out.println(d.toJson());
				                 }
				             }
				         }

				         scanner.close();
				         mongoClient.close();
				     }
}
