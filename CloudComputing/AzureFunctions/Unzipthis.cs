using System;
using System.IO;
using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Host;
using Microsoft.Extensions.Logging;

namespace Unzipthis.Function
{
    public static class Unzipthis
    {
        [FunctionName("Unzipthis")]
        public static void Run([BlobTrigger("samples-workitems/{name}", Connection = "AzureWebJobsStorage")]Stream myBlob, string name, ILogger log)
        {
            log.LogInformation($"C# Blob trigger function Processed blob\n Name:{name} \n Size: {myBlob.Length} Bytes");
            
            string destinationStorage = Environment.GetEnvironmentVariable("destinationStorage");
            string destinationContainer = Environment.GetEnvironmentVariable("destinationContainer");

            try{
                if(name.Split('.').Last().ToLower() == "zip"){

                    //ZipArchive archive = new ZipArchive(myBlob);

                    CloudStorageAccount storageAccount = CloudStorageAccount.Parse(destinationStorage);
                    CloudBlobClient blobClient = storageAccount.CreateCloudBlobClient();
                    CloudBlobContainer container = blobClient.GetContainerReference(destinationContainer);
                    
                    using(MemoryStream blobMemStream = new MemoryStream()){

                        await myBlob.DownloadToStreamAsync(blobMemStream);

                        using(ZipArchive archive = new ZipArchive(blobMemStream))
                        {
                            foreach (ZipArchiveEntry entry in archive.Entries)
                            {
                                log.LogInformation($"Now processing {entry.FullName}");

                                //Replace all NO digits, letters, or "-" by a "-" Azure storage is specific on valid characters
                                string valideName = Regex.Replace(entry.Name,@"[^a-zA-Z0-9\-]","-").ToLower();

                                CloudBlockBlob blockBlob = container.GetBlockBlobReference(valideName);
                                using (var fileStream = entry.Open())
                                {
                                    await blockBlob.UploadFromStreamAsync(fileStream);
                                }
                            }
                        }
                    }
                }
            }
            catch(Exception ex){
                log.LogInformation($"Error! Something went wrong: {ex.Message}");

            } 
        
        }
    }
}
