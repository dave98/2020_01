package com.amazonaws.samples;

import java.util.*;
import com.amazonaws.AmazonClientException;
import com.amazonaws.auth.AWSCredentials;
import com.amazonaws.auth.AWSStaticCredentialsProvider;
import com.amazonaws.auth.profile.ProfileCredentialsProvider;
import com.amazonaws.regions.Regions;
import com.amazonaws.services.elasticmapreduce.AmazonElasticMapReduce;
import com.amazonaws.services.elasticmapreduce.AmazonElasticMapReduceClientBuilder;
import com.amazonaws.services.elasticmapreduce.model.*;
import com.amazonaws.services.elasticmapreduce.util.StepFactory;

public class Main {

	public static void main(String[] args) {
		
		AWSCredentials credentials_profile = null;
		try {
			credentials_profile = new ProfileCredentialsProvider("default").getCredentials();
			System.out.println("Credenciales obtenidos");
		}
		catch (Exception e) {
			throw new AmazonClientException("No se puede cargar las credenciales de .aws/credentials files" +
											"Asegurate que el archivo de credenciales exista con el nombre especificado" , e);
		}
		
		AmazonElasticMapReduce emr = AmazonElasticMapReduceClientBuilder.standard()
										.withCredentials(new AWSStaticCredentialsProvider(credentials_profile))
										.withRegion(Regions.US_EAST_1).build();
		StepFactory stepFactory = new StepFactory();
		StepConfig enabledebugging = new StepConfig().withName("Enable debugging").withActionOnFailure("TERMINATE_JOB_FLOW").withHadoopJarStep(stepFactory.newEnableDebuggingStep());
		
		Application spark = new Application().withName("Spark");
		
		RunJobFlowRequest request = new RunJobFlowRequest()
										.withName("Dave Spark Cluster")
										.withReleaseLabel("emr-5.20.0")
										.withSteps(enabledebugging)
										.withApplications(spark)
										.withLogUri("s3://aws-logs-363327130116-us-east-1/elasticmapreduce/")
											.withServiceRole("EMR_DefaultRole")
											.withJobFlowRole("EMR_EC2_DefaultRole")
										.withInstances(new JobFlowInstancesConfig()
												.withEc2SubnetId("subnet-12ab3c45")
												.withEc2KeyName("myEc2Key")
												.withInstanceCount(3)
												.withKeepJobFlowAliveWhenNoSteps(true)
												.withMasterInstanceType("m4.large")
												.withSlaveInstanceType("m4.large")
											);
		RunJobFlowResult result = emr.runJobFlow(request);
		System.out.println("El ID del cluster es: " + result.toString());
	}

}
