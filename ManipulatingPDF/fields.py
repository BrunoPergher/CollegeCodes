from PyPDF2 import PdfReader

def list_pdf_fields(pdf_path):
    reader = PdfReader(pdf_path)
    fields = reader.get_fields()

    if fields:
        print("Form fields found:")
        for field_name, field_info in fields.items():
            print(f"Field Name: {field_name}")
            print(f"Field Info: {field_info}\n")
    else:
        print("No form fields found in the PDF.")

# Usage
list_pdf_fields('avaliacaoempresaeditavel.pdf')
