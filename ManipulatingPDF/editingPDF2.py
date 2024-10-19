from PyPDF2 import PdfReader, PdfWriter
from PyPDF2.generic import NameObject, BooleanObject

def fill_pdf_specific_page(input_pdf_path, output_pdf_path, data_dict, page_to_edit=1):
    reader = PdfReader(input_pdf_path)
    writer = PdfWriter()

    # Add all pages to the writer initially
    writer.append_pages_from_reader(reader)

    # Access the specific page containing form fields
    page = reader.pages[page_to_edit]

    # Find and update the form fields on the specified page
    annotations = page.get('/Annots')
    if annotations:
        for annot in annotations:
            annot_obj = annot.get_object()
            field_name = annot_obj.get('/T')
            if field_name:
                # Trim any extra symbols if needed
                field_name_str = field_name.strip('()')
                if field_name_str in data_dict:
                    annot_obj.update({
                        NameObject('/V'): data_dict[field_name_str]
                    })
                    print(f"Updated field '{field_name_str}' with value '{data_dict[field_name_str]}'")

    # Set NeedAppearances flag to ensure the values are visible
    if '/AcroForm' in reader.trailer['/Root']:
        form = reader.trailer['/Root']['/AcroForm']
        form.update({
            NameObject('/NeedAppearances'): BooleanObject(True)
        })

    # Write the updated PDF
    with open(output_pdf_path, 'wb') as output_stream:
        writer.write(output_stream)
    print(f"Filled PDF saved as '{output_pdf_path}'")

# Data to fill in
data = {
    'nome': 'John Doe',
    'empresa': 'Acme Corp',
    'periodo': '2023-10'
}

# Usage - Specify the page to edit (0 for first page, 1 for second page, etc.)
fill_pdf_specific_page('editavel.pdf', 'filled_form.pdf', data, page_to_edit=1)
