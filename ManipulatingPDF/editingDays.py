import fitz

def fill_pdf_pymupdf(input_pdf_path, output_pdf_path, data_dict):
    doc = fitz.open(input_pdf_path)

    # Iterate through each page and fill the widgets (form fields)
    for page in doc:
        widgets = page.widgets()  # Get all form fields (widgets) on the page
        if widgets:
            for field in widgets:
                field_name = field.field_name
                if field_name in data_dict:
                    field.field_value = data_dict[field_name]
                    field.update()

    # Save the filled PDF
    doc.save(output_pdf_path, incremental=False, deflate=True)
    print(f"Filled PDF saved as '{output_pdf_path}'")

    # Flatten the PDF to remove interactive form elements
    doc = fitz.open(output_pdf_path)
    for page in doc:
        page.clean_contents()  # Remove any interactive form fields to make content static
    flattened_output_path = 'flattened_' + output_pdf_path
    doc.save(flattened_output_path, deflate=True)
    print(f"Flattened PDF saved as '{flattened_output_path}'")

# New Data to fill in (Portuguese content)
data = {
    'nome_estagiario': 'João da Silva',
    'nome_empresa': 'Empresa Exemplo S.A.',
    'nome_mes': 'Outubro 2023',
    'nome_estagiario2': 'João da Silva',  # Same as nome_estagiario
    'nome_empresa2': 'Empresa Exemplo S.A.',  # Same as nome_empresa
    'nome_mes2': 'Outubro 2023',  # Same as nome_mes
    'observacoes': 'João demonstrou ótima adaptação e desempenho durante o período de estágio.'
}

# Fill in daily data (1 to 31) with sample times and descriptions
for day in range(1, 32):
    day_str = f"{day:02d}"  # Format day as two digits (e.g., "01", "02", ..., "31")
    data[f'entrada_{day_str}'] = '08:00'  # Sample entry time
    data[f'saida_{day_str}'] = '17:00'  # Sample exit time
    data[f'descricao_{day_str}'] = f'Atividades realizadas no dia {day}.'  # Sample description
    data[f'horas_{day_str}'] = '8'  # Total hours worked

# Usage
fill_pdf_pymupdf('acompanhamento_estagio_editavel.pdf', 'acompanhamento.pdf', data)