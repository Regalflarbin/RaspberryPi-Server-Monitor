#include <string>

#include <stdio.h>
#include <string.h>
#include <errno.h>


class SendMail{
public:
	int sendmail(const char *to, const char *from, const char *subject, const char *message)
	{
		int retval = -1;
		FILE *mailpipe = popen("/usr/lib/sendmail -t", "w");
		if (mailpipe != NULL) {
			fprintf(mailpipe, "To: %s\n", to);
			fprintf(mailpipe, "From: %s\n", from);
			fprintf(mailpipe, "Subject: %s\n\n", subject);
			fwrite(message, 1, strlen(message), mailpipe);
			fwrite("\n", 1, 2, mailpipe);
			pclose(mailpipe);
			retval = 0;
		}
		else {
			perror("Failed to invoke sendmail");
		}
		return retval;
	}

	void testEmail() // for testing
	{
		sendmail("henx125@gmail.com", "henx125@gmail.com", "Test Email", "apples");

		printf("Test email sent.\n");
	}

	void systemStartEmail() // to be invoked upon program first start
	{
		sendmail("henx125@gmail.com", "henx125@gmail.com", "Server Monitoring Started",
			"This email was sent to confirm that the system has started properly and email communications are not failing.");

		printf("Monitoring systems started\n");
		printf("Confirmation Email Sent\n");
	}

	void optimalTempEmail() // to be invoked when server room temperature has returned to acceptable values
	{
		sendmail("henx125@gmail.com", "henx125@gmail.com", "Server Ambience Optimal",
			"This email was sent to confirm that temperature readings are now within acceptable ranges.");

		printf("Optimal temperature email sent.\n");
	}

	void optimalHumidEmail() // to be invoked when server room humidity has returned to acceptable values
	{
		sendmail("henx125@gmail.com", "henx125@gmail.com", "Server Ambience Optimal",
			"This email was sent to confirm that humidity readings are now within acceptable ranges.");

		printf("Optimal humidity email sent.\n");
	}

	void highTempEmail() // to be invoked when temperature readings are above acceptable values
	{
		sendmail("henx125@gmail.com", "henx125@gmail.com", "Warning: Server Room too Hot",
			"This email was sent to warn of HIGH TEMPERATURE readings in the server room. Please be advised.");

		printf("High temperature warning email sent.\n");
	}

	void highHumidEmail() // to be invoked when humidity readings are above acceptable values
	{
		sendmail("henx125@gmail.com", "henx125@gmail.com", "Warning: Server Room too Humid",
			"This email was sent to warn of HIGH HUMIDITY readings in the server room. Please be advised.");

		printf("High humidity warning email sent.\n");
	}

	void smokeEmail() // to be invoked when smoke has been detected
	{
		sendmail("henx125@gmail.com", "henx125@gmail.com", "WARNING: Smoke Detected in Server Room",
			"This email was sent to warn of SMOKE and possible fire in the server room. Please seek immediate action.");

		printf("Smoke detection email sent.\n");
	}

	void fireEmail() // to be invoked when fire has been detected
	{
		sendmail("henx125@gmail.com", "henx125@gmail.com", "WARNING: Fire Detected in Server Room",
			"This email was sent to warn of FIRE in the server room. Please seek immediate action and get to saftey.");

		printf("Fire detection email sent.\n");
	}
};
